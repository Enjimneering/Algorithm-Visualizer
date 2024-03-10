#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//CONSTANT DECLARATIONS

//Graphics (SDL) global variables.
#define HEIGHT 600
#define WIDTH 600
SDL_Window* window;
SDL_Renderer* renderer;

//Sorting  
const int ARRAY_SIZE = 20;

//Function Protoypes

//Initialization
int SDL_SETUP();
void InitArray(int _array[] , int _arraySize);

//Processing
int findMax(int _array[], int _arraySize);
int findMin(int _array[], int _arraySize);
int CalculateScaleFactor(int _array[] , int _arraySize , int _maxValue );
void swapIndexes(int _array[], int index1, int index2);
void SelectionSort(int _array[] , int _arraySize, SDL_Renderer* _renderer , int _scaleFactor , int _maxArrValue);

//Output
void PrintArray(int _array[], int _arraySize);
void DrawState();


int main(int argc, char** argv)
{
    SDL_SETUP(); // SDL Boilerplate Code

    //Create unsorted array of random values 
    int array[1024];
    InitArray(array, ARRAY_SIZE );
    int maxArrayValue = findMax(array,ARRAY_SIZE);

    //Setup the Visualiser Screen
    int displayScaleFactor = CalculateScaleFactor(array, ARRAY_SIZE, maxArrayValue);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);

    DrawState(array, ARRAY_SIZE, renderer, displayScaleFactor, maxArrayValue, -1 , -1 , -1 );

    SelectionSort(array, ARRAY_SIZE, renderer,displayScaleFactor , maxArrayValue);

    int running = 1;
    while(running) // program loop
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = 0;
                    break;

                default:
                    break;
            }
        }
        
    
    }
        
    return 0;
}


int SDL_SETUP() // Initialize Video - window & renderer
{
    printf("\n Initializing SDL");

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
            printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
            return 1;
        }

        printf(".");

        window = SDL_CreateWindow("Sort Algorithm Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,  WIDTH , HEIGHT , 0);
        if(!window){
            printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
            return 1;
        }
         printf(".");

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer){
            printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
            return 1;
        }
         printf(".");

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    printf("\n SDL Initialization Complete!");
}

void SDL_ClearWindow(SDL_Renderer* _renderer)
{
    SDL_SetRenderDrawColor(_renderer, 0,0,0,255);
    SDL_RenderClear(_renderer);

}
void InitArray(int _array[] , int _arraySize)
{
    time_t current_time;
    srand((unsigned)time (&current_time)); // random seed gen
    
    printf("\n Creating Array..");
    for (size_t i = 0; i < _arraySize; i++)
    {
        _array[i] = rand() %50 + 1;
    }
    printf(".");

    PrintArray(_array , _arraySize);
}

void PrintArray(int _array[], int _arraySize)
{

    printf("\n Array = [ ");
    for (short i = 0; i < _arraySize - 1; i++)
    {   
       printf("%d , ", _array[i] );
    }
 
    printf("%d ]", _array[_arraySize - 1] );

}

int CalculateScaleFactor(int _array[] , int _arraySize , int _maxValue )
{
    int displayScaleFactor = (HEIGHT * 0.95) / _maxValue;

    return displayScaleFactor; 
}


void DrawState(int _array[] , int _arraySize, SDL_Renderer* _renderer, int _scaleFactor, int _maxArrValue , int red , int blue , int green )
{
    SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // default to white boxes
    int maxRectHeight = _maxArrValue * _scaleFactor;
    
    for (size_t i = 0; i < _arraySize; i++)
    {
       SDL_Rect dataRect;

       dataRect.h = _array[i] * _scaleFactor;
       dataRect.w = WIDTH/ (ARRAY_SIZE) - 2;
       dataRect.x = i * (WIDTH/(ARRAY_SIZE)) ; 
       dataRect.y =  (_maxArrValue + (_maxArrValue -_array[i] )) * (_scaleFactor) - maxRectHeight + WIDTH/20 ;

        printf("\n Drawn index %d - { %d }, at  [%d , %d] , width = %d , height = %d ", i , _array[i], dataRect.x , dataRect.y , dataRect.h, dataRect.w);
       
       if ( green == 1){
        SDL_SetRenderDrawColor(_renderer, 0, 255 , 0 , 255);
       }

       else if (i == blue){
        SDL_SetRenderDrawColor(_renderer, 0, 0, 255, 255);
       }

       if ( i == red){
        SDL_SetRenderDrawColor(_renderer, 255, 0 , 0 , 255);
       }
       SDL_RenderFillRect(_renderer , &dataRect);
       SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255); // default to white boxes
    }
    
}


void SelectionSort(int _array[] , int _arraySize, SDL_Renderer* _renderer , int _scaleFactor , int _maxArrValue)
{
    printf("\n Sorting.");

    for(int i = 0; i < _arraySize ; i++)
    {
     printf(".");

        for(int j = i + 1 ; j < _arraySize ; j++)
        {
            //Clear Canvas
            SDL_SetRenderDrawColor(_renderer, 0,0,0,255);
            SDL_RenderClear(_renderer);

            //Set next block to white
            SDL_SetRenderDrawColor(_renderer, 255,255,255,255);
             
                if (_array[j] < _array[i]) // buble sort ???
                {
                    swapIndexes( _array  , j, i);
                    //printf("\n index %d swapped with index %d", j , i);
                }
                
                SDL_Delay(100);

                DrawState(_array, _arraySize, _renderer, _scaleFactor, _maxArrValue, j , i , -1 );
                SDL_RenderPresent(renderer);
        }
            
    }
    printf(" Sort Completed! \n ");
    
    //Clear Canvas
    SDL_SetRenderDrawColor(_renderer, 0,0,0,255);
    SDL_RenderClear(_renderer);
  
    //Final Output
    
    DrawState(_array, _arraySize, _renderer, _scaleFactor, _maxArrValue, -1 ,-1 , -1 );
    SDL_RenderPresent(renderer);
    PrintArray(_array ,_arraySize );
}



// put these in a separate header file later
int findMax(int _array[], int _arraySize)
{
    int max = _array[0];
    int maxIndex = 0;


    for (size_t i = 1; i < _arraySize; i++)
    {
         if (_array[i] > max)
         {
            max = _array[i]; 
            maxIndex = i;
         }
    }
    
    printf("\n The Max value was: %d at index %d", max, maxIndex);
    return max;

}

int findMin(int _array[], int _arraySize)
{
    int min = _array[0];

    for (size_t i = 1; i < _arraySize; i++)
    {
         if (_array[i] < min)
         min = _array[i]; 
    }
    
    return min;

}

void swapIndexes(int _array[], int index1, int index2)
{
    int temp = _array[index1];
    _array[index1] = _array[index2];
     _array[index2] = temp;
}



