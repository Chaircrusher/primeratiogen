#include "Bjorklund.h"

//Edited NoisyLittleBurger's Bjorklund Algorithm in C
//http://www.noisylittlebugger.net/diy/bjorklund/Bjorklund_Working_Final/Bjorklund_algorithm_arduino.txt
//CHANGED :
//1. use dynamic array.
//2. fixed sequence's off-spot problem
//3. added Explanation about Algorithm based on G.Touissant's Paper,
//"The Euclidean Algorithm Generates Traditional Musical Rhythms"
//
//--------------------------------------------------------------
void Bjorklund::init(){
    try{
        iter();
        
    }catch(out_of_range){
        cerr<<"pulse::out_of_range"<<'\n';
    }
}
void Bjorklund::init(int step, int pulse){
    lengthOfSeq = step;
    pulseAmt = pulse;
    
    try{
        iter();
        
    }catch(out_of_range){
        cerr<<"pulse::out_of_range"<<'\n';
    }
}
void Bjorklund::iter(){
    //\Bjorklund algorithm
    //\do E[k,n]. k is number of one's in sequence, and n is the length of sequence.
    int divisor = lengthOfSeq - pulseAmt; //initial amount of zero's
    if(divisor < 0) throw out_of_range{"Divisor has to be greator than 0"};
    
    remainder.push_back(pulseAmt);
    //iteration
    int index = 0; //we start algorithm from first index.
    
    while(true){
        count.push_back(std::floor(divisor / remainder[index]));
        remainder.push_back(divisor % remainder[index]);
        divisor = remainder.at(index);
        index += 1; //move to next step.
        if(remainder[index] <= 1){
            break;
        }
    }
    count.push_back(divisor);
    buildSeq(index); //place one's and zero's
    reverse(sequence.begin(), sequence.end());
    
    //position correction. some of result of algorithm is one step rotated.
    int zeroCount =0;
    if(sequence.at(0) != 1){
        do{
            zeroCount ++;
        }while(sequence.at(zeroCount) == 0);
        std::rotate(sequence.begin(), sequence.begin() + zeroCount, sequence.end());
    }
}
void Bjorklund::buildSeq(int slot){
    //construct a binary sequence of n bits with k one‚Äôs, such that the k one‚Äôs are distributed as evenly as possible among the zero‚Äôs
    
    if (slot == -1) {
        sequence.push_back(0);
    }
    else if (slot == -2)  {
        sequence.push_back(1);
    }else{
        for (int i = 0; i < count[slot]; i++)
            buildSeq(slot-1);
        if (remainder[slot] !=0)
            buildSeq(slot-2);
    }
}
void Bjorklund::print(){
    for(int i=0; i != sequence.size();i++){
        cout<<sequence.at(i);
    }
    cout<<'\n';
    cout<<"Size : "<<sequence.size()<<'\n';
}
vector<bool> Bjorklund::LoadSequence(){
    vector<bool> seq;
    for(int i=0;i < lengthOfSeq;i++){
        seq.push_back(sequence[i]);
    }
    return seq;
}
