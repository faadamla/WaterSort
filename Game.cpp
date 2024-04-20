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

long long int numberOfInitialStates(uc NumberOfTubes, uc DepthOfTube, uc zeros=2){
    return factorial((NumberOfTubes-zeros)*DepthOfTube)/pow(factorial(DepthOfTube),(NumberOfTubes-zeros))/factorial(NumberOfTubes-zeros);
}

template<uc NumberOfTubes, uc DepthOfTube>
std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> generateStates_fillIndex_v1(unsigned int index, uc zerotubes, const std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> &generatedUntilPreviousIndex){
    if(index==0){
        std::array<uc, NumberOfTubes*DepthOfTube> a, b;
        a.fill(0);
        b.fill(0);
        b[0]=1;
        return {a, b};
    }
    else{
        std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> returnvec;
        uc max_element;
        std::array<uc, NumberOfTubes*DepthOfTube> arCopy;
        for(auto&& ar: generatedUntilPreviousIndex){
            max_element = *(std::max_element(ar.begin(), ar.begin() + index)); //Max element before index i
            arCopy = ar;
            for (uc e=1; e<=std::min(max_element+1, NumberOfTubes-zerotubes); e++){
                if (std::count(arCopy.begin(), arCopy.end(), e) < DepthOfTube){
                    arCopy[index] = e;
                    returnvec.emplace_back(arCopy);
                }
            }
        }
        return returnvec;
    }
}

template<uc NumberOfTubes, uc DepthOfTube>
std::set<State<NumberOfTubes,  DepthOfTube>> allUniqueInitialState(uc empty=2){
    std::array<uc, NumberOfTubes*DepthOfTube> arr;
    arr.fill(0);
    std::vector<std::array<uc, NumberOfTubes*DepthOfTube>> resutVector{arr};
    for(uc i=empty*DepthOfTube; i<NumberOfTubes*DepthOfTube; i++){
        resutVector = generateStates_fillIndex_v1<NumberOfTubes, DepthOfTube>(i, empty, resutVector);
    }
    auto size = resutVector.size();
    std::cout << "Initial vector size is: " << size;
    std::set<State<NumberOfTubes,  DepthOfTube>> resultSet{};
    unsigned short int j=0;
    for(auto&& arr: resutVector){
        resultSet.emplace(State<NumberOfTubes, DepthOfTube>(arr));
        if(resultSet.size() == pow(10, j)){
            std::cout << "Found unique states are: 10^" <<j<<std::endl;
            ++j;
        }
    }

    return resultSet;
}
