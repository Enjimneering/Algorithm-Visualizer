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


//Output
void PrintArray(int _array[], int _arraySize);
void DrawState();




int main(int argc, char** argv)
{
    SDL_SETUP(); // SDL Boilerplate Code

    int array[256];
    InitArray(array, ARRAY_SIZE );
    PrintArray(array , ARRAY_SIZE);
    int maxArrayValue = findMax(array,ARRAY_SIZE);
   
   
   
   
    int displayScaleFactor = CalculateScaleFactor(array, ARRAY_SIZE, maxArrayValue);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    DrawState(array, ARRAY_SIZE, renderer, displayScaleFactor, maxArrayValue);

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
        
        SDL_RenderPresent(renderer);
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

    printf("\n SDL initialization complete !");
}

void InitArray(int _array[] , int _arraySize)
{
    time_t current_time;
    srand((unsigned)time (&current_time)); // random seed gen
    
    for (size_t i = 0; i < _arraySize; i++)
    {
        _array[i] = rand() % 50 + 1;
    }


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

void DrawState(int _array[] , int _arraySize, SDL_Renderer* _SDLrenderer , int _scaleFactor , int _maxArrValue)
{

    int maxRectHeight = _maxArrValue * _scaleFactor;


    for (size_t i = 0; i < _arraySize; i++)
    {
       SDL_Rect dataRect;

       dataRect.h = _array[i] * _scaleFactor;
       dataRect.w = WIDTH/ (ARRAY_SIZE) - 2;
       dataRect.x = i * (WIDTH/(ARRAY_SIZE)) ; 
       dataRect.y =  (_maxArrValue + (_maxArrValue -_array[i] )) * (_scaleFactor) - maxRectHeight + WIDTH/20 ;

       printf("\n Drawn index %d - { %d }, at  [%d , %d] , width = %d , height = %d ", i , _array[i], dataRect.x , dataRect.y , dataRect.h, dataRect.w);
       SDL_RenderFillRect(_SDLrenderer , &dataRect);
    }
    


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





