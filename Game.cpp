#include "State.cpp"
#include<cmath>

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

long long int numberOfInitialStates(uc NumberOfTubes, uc DepthOfTube){
    return factorial(NumberOfTubes*DepthOfTube)/pow(factorial(DepthOfTube),NumberOfTubes)/factorial(NumberOfTubes);
}

template<uc NumberOfTubes, uc DepthOfTube>
std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> generateAllUniqueStates_fillIndex_v1(unsigned int index, const &std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> generatedUntilPreviousIndex){
    if(index==0){
        std::array<uc, NumberOfTubes*DepthOfTube> a, b;
        a.fill(0);
        b=0;
        b[0]=1
        return {a, b}
    }
    else{
        std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> returnvec;
        uc max_element;
        std::array<uc, NumberOfTubes*DepthOfTube> arCopy;
        for(auto&& ar: generatedUntilPreviousIndex){
            max_element = *(std::max_element(ar.begin(), ar.begin() + i)); //Max element before index i
            arCopy = ar;
            for (uc e=1; e<=max_element+1; e++){
                if (std::count(arCopy.begin(), arCopy.end(), e) < DepthOfTube)
                arCopy[i] = e;
                returnvec.emplace_back(arCopy);
            }
        }
    }
}

template<uc NumberOfTubes, uc DepthOfTube>
std::vector<State<NumberOfTubes,  DepthOfTube>> allUniqueInitialState(uc empty=2){

}
