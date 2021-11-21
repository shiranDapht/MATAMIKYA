#ifndef ASNODE_H_
#define ASNODE_H_

typedef struct asNode_t* asNode;
// Node struct
struct asNode_t{
    ASElement data;
    double amount;
    asNode next;
};

void asNodeCreate(asNode node ,ASElement element);

#endif /* ASNODE_H_ */