#include "State.cpp"

template<uc NumberOfTubes, uc DepthOfTube>
std::vector<State<NumberOfTubes,  DepthOfTube>> allInitialState(uc ncolors, uc empty=2){

}

long long int factorial(unsigned int n){
    if(n<=1){return 1;}
    else{
        long long int x=1;
        for(unsigned int i=2;i<=n; i++){
            x *= i;
        }
        return x;
    }
}