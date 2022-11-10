#include <bits/stdc++.h>
#include "vector.h"
#include "../../source/tests/include/tm/test_manager.h"

template<typename T>
void printVector(const sc::vector<T>& vector,std::string name){
    std::cout << "Vector"<<name<<": ";
    for(size_t i{0};i<vector.size();i++){
        std::cout << vector[i] << " "; 
    }
    std::cout << std::endl;
}

int main(){
    setlocale(LC_ALL, "portuguese");
    sc::vector<int>vectorA;
    sc::vector<int>vectorB {1,2,3,4,5};
    //sc::vector<int>vectorB(5);

    std::cout << "VectorA Inicial ("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    vectorA.push_back(1);
    vectorA.push_back(2);
    vectorA.push_back(3);
    vectorA.push_back(4);
    vectorA.push_back(5);

    std::cout << "VectorA PushBack("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    vectorA.pop_back();
    vectorA.pop_back();
    vectorA.pop_back();

    std::cout << "VectorA PopBack("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Front: " << vectorA.front() <<std::endl;
    std::cout << "Back: " << vectorA.back() <<std::endl;

    std::cout << "/////////////////////////////////////////////////////////////////////////////\n\n";
    
    std::cout << "VectorB Initial("<<vectorB.size()<<"): ";
    for(size_t i{0} ; i < vectorB.size(); i++){
        std::cout << vectorB[i] << " ";
    }
    std::cout << std::endl;

    vectorB.push_back(6);
    vectorB.push_back(7);
    vectorB.push_back(8);
    vectorB.push_back(9);
    vectorB.push_back(10);

    std::cout << "VectorB PushBack("<<vectorB.size()<<"): ";
    for(size_t i{0} ; i < vectorB.size(); i++){
        std::cout << vectorB[i] << " ";
    }
    std::cout << std::endl;

    vectorB.pop_back();
    vectorB.pop_back();
    vectorB.pop_back();

    std::cout << "VectorB PopBack("<<vectorB.size()<<"): ";
    for(size_t i{0} ; i < vectorB.size(); i++){
        std::cout << vectorB[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "FrontB: " << vectorB.front() <<std::endl;
    std::cout << "BackB: " << vectorB.back() <<std::endl;
    std::cout << "/////////////////////////////////////////////////////////////////////////////\n\n";

    std::cout << "VectorA Antes("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "VectorB Antes("<<vectorB.size()<<"): ";
    for(size_t i{0} ; i < vectorB.size(); i++){
        std::cout << vectorB[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    //vectorA = vectorB;
    vectorB = vectorA;
    std::cout << "VectorA Depois("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "VectorB Depois("<<vectorB.size()<<"): ";
    for(size_t i{0} ; i < vectorB.size(); i++){
        std::cout << vectorB[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "/////////////////////////////////////////////////////////////////////////////\n\n";
    
    std::cout << "VectorA Antes("<<vectorA.size()<<"): ";
    for(size_t i{0} ; i < vectorA.size(); i++){
        std::cout << vectorA[i] << " ";
    }
    std::cout << std::endl;

    printVector(vectorB,"B Antes");

    vectorB = vectorA = {16,17,18,19,20};

    sc::vector<int>vectorC(vectorA);

    sc::vector<int>vectorD(vectorA.begin(),vectorA.end());

    printVector(vectorA,"A Depois");

    printVector(vectorB,"B Depois");

    printVector(vectorC,"C Inicial");

    std::cout << "/////////////////////////////////////////////////////////////////////////////\n\n";
    
    std::cout << "Iterating over vectorD: [ ";
    auto it = vectorD.begin();
    while(it!=vectorD.end()){
        std::cout << *it << " ";
        it++;
    }
    std::cout << "]\n";

    printVector(vectorD,"D Inicial");

    //auto it1 = vectorD.begin();
    //auto it2 = vectorD.end();

    vectorA = vectorB;

    if(vectorA==vectorB){
        std::cout << "Iguais\n";
    }else{
        std::cout << "Diferentes\n";
    }

    vectorA.push_back(55);

    if(vectorA!=vectorB){
        std::cout << "Funcionando\n";
    }else{
        std::cout << "Error\n";
    }

    vectorA.push_front(99);

    printVector(vectorA,"A push_front(99)");

    std::cout << "Valor Na 2ª Posição: " << vectorA.at(2) << std::endl;

    std::cout << "Capacidade do vectorA Antes: " << vectorA.capacity() << std::endl;

    vectorA.reserve(20);

    std::cout << "Capacidade do vectorA Depois: " << vectorA.capacity() << std::endl;

    printVector(vectorA,"A Antes Dos shrink_to_fit");
    std::cout << "Capacidade do vectorA Antes: " << vectorA.capacity() << std::endl;

    vectorA.shrink_to_fit();

    printVector(vectorA,"A Depois Dos shrink_to_fit");
    std::cout << "Capacidade do vectorA Depois: " << vectorA.capacity() << std::endl;

    sc::vector<int>vectorE;

    printVector(vectorE,"E Antes do assign()");
    vectorE.assign(5,16);
    printVector(vectorE,"E Depois do assign()1");
    vectorE.assign({1,2,3,4,5});
    printVector(vectorE,"E Depois do assign()2");

    printVector(vectorA,"A Antes do Erase");
    //auto it3 = vectorA.begin();
    vectorA.erase(it);
    printVector(vectorA,"A Depois do Erase");

    auto it4 = vectorA.end();
    auto it5 = vectorA.begin();

    auto x = it4-it5;

    std::cout << x << std::endl;
    
    sc::vector<int> vectorF(10);
    printVector(vectorF,"F Inicial");
    std::cout << "m_end: " << vectorF.size() << std::endl;
    std::cout << "m_capacity: " << vectorF.capacity() << std::endl;
    printVector(vectorF,"F Depois");

    sc::vector<int> vectorG;
    printVector(vectorG,"G Inicial");
    std::cout << "m_end: " << vectorG.size() << std::endl;
    std::cout << "m_capacity: " << vectorG.capacity() << std::endl;

    vectorG.push_back(1);
    printVector(vectorG,"G Depois");
    std::cout << "m_end: " << vectorG.size() << std::endl;
    std::cout << "m_capacity: " << vectorG.capacity() << std::endl;

    std::cout << "////////////////////////std::vector//////////////////////////\n";
    sc::vector<int> myvector{1,2,3,4,5,6,7,8};

    std::cout << "size: " << (int) myvector.size() << '\n';
    std::cout << "capacity: " << (int) myvector.capacity() << '\n';
    //std::cout << "max_size: " << (int) myvector.max_size() << '\n';

    printVector(myvector,"MyVector Antes");
    
    //myvector.erase(myvector.begin()+1);
    myvector.erase(myvector.begin()+2,myvector.begin()+5);

    printVector(myvector,"MyVector Depois");

    sc::vector<int> teste{1,2,3,4,5,6,7,8};

    auto past_last = teste.erase( teste.begin(), std::next(teste.begin(),3) );

    if(teste.begin()==past_last){
        std::cout << "Iguais\n";
    }else{
        std::cout << "Diferentes\n";
    }

    sc::vector<int> vectorH{1,2,3,4,5,6,7,8};

    printVector(vectorH,"H Antes do Assign");
    vectorH.assign(vectorH.begin()+2,vectorH.begin()+6);
    printVector(vectorH,"H Depois do Assign");
    std::cout << "m_end: " << vectorH.size() << std::endl;
    std::cout << "m_capacity: " << vectorH.capacity() << std::endl;
    vectorH.push_back(11);
    printVector(vectorH,"H");
    std::cout << "m_end: " << vectorH.size() << std::endl;
    std::cout << "m_capacity: " << vectorH.capacity() << std::endl;

    vectorH.insert(vectorH.begin(), 13);
    printVector(vectorH,"H");
    std::cout << "m_end: " << vectorH.size() << std::endl;
    std::cout << "m_capacity: " << vectorH.capacity() << std::endl;

    std::cout << "//////////////////////////////////////////////////////////////////////\n";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    sc::vector<int> aux{6,7,8,9,10};
  
    sc::vector<int> teste1{1,2,3,4,5};
    
    //teste1.insert(teste1.begin(), aux.begin(), aux.end());
    //teste1.insert(std::next( teste1.begin(), 2 ), aux.begin(), aux.end());
    //teste1.insert( teste1.end(), aux.begin(), aux.end() );
    
    teste1.insert(teste1.begin(), {12,13,14,15,16});
    printVector(teste1," ");
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    sc::vector<int> teste2;
    std::vector<int> testeOr2;

    testeOr2.insert(testeOr2.begin(),99);

    std::cout << "Vector: ";
    for(size_t i{0};i<testeOr2.size();i++){
        std::cout << testeOr2[i] << " "; 
    }
    std::cout << std::endl;

    testeOr2.insert(testeOr2.begin(),999);

    std::cout << "Vector: ";
    for(size_t i{0};i<testeOr2.size();i++){
        std::cout << testeOr2[i] << " "; 
    }
    std::cout << std::endl;

    std::cout << "m_end: " << testeOr2.size() << std::endl;
    std::cout << "m_capacity: " << testeOr2.capacity() << std::endl;
    std::cout << std::endl;

    teste2.insert(teste2.begin(),99);
    printVector(teste2, " Insert Vazio no Inicio");
    std::cout << "m_end: " << teste2.size() << std::endl;
    std::cout << "m_capacity: " << teste2.capacity() << std::endl;

    std::cout << std::endl;

    //sc::vector<int> teste3;
    //teste3.insert(teste3.begin()+1,555);
    //printVector(teste3, " Insert Vazio Depois do Inicio");
    //std::cout << "m_end: " << teste3.size() << std::endl;
    //std::cout << "m_capacity: " << teste3.capacity() << std::endl;

    sc::vector<int>vec;
    

    sc::vector<int>vec1;

    printVector(vec,"Antes");
    std::cout << "m_end: " << vec.size() << std::endl;
    std::cout << "m_capacity: " << vec.capacity() << std::endl;
    vec.insert( vec.begin(), 0);

    printVector(vec,"Depois");
    std::cout << "m_end: " << vec.size() << std::endl;
    std::cout << "m_capacity: " << vec.capacity() << std::endl;

    std::cout << std::endl;


    printVector(vec1,"Antes");
    std::cout << "m_end: " << vec1.size() << std::endl;
    std::cout << "m_capacity: " << vec1.capacity() << std::endl;
    std::cout << std::endl;

    //vec1.insert( vec1.begin()+1, 0 );

    //printVector(vec1,"Throw");
    //std::cout << "m_end: " << vec1.size() << std::endl;
    //std::cout << "m_capacity: " << vec1.capacity() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    sc::vector<int> a(0);
    printVector(a,"With newCapacity");
    std::cout << "m_end: " << a.size() << std::endl;
    std::cout << "m_capacity: " << a.capacity() << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////////////////////////////////////////////////////\n";

    std::vector<int> auxiliar{1,2,3,4,5,6,7,8};

    //std::cout << "Testando Acessar Posição Fora do Range: (" << auxiliar[1542] << ")\n";
    return 0;
}