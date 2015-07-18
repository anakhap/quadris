#ifndef quadris_quadris_h
#define quadris_quadris_h

#include "board.h"

enum Shapes {NoShape, Jshape, Lshape, Sshape, Oshape, Zshape, Tshape, Ishape};


class AbstractBlock {
private:
    
    Shapes chosenpiece;
    

public:
 
    int coords[4][2];
    void SetShape(Shapes block); 
    
    AbstractBlock() { SetShape(NoShape); }
    Shapes GetShape() const { return chosenpiece; }
    virtual ~AbstractBlock() = 0;
    
    virtual void show(Board &b)=0;
    virtual void clockwise(Board &b)=0;
    virtual void counterclockwise(Board &b)=0;
    virtual void right(Board &b)=0;
    virtual void left(Board &b)=0;
    virtual void down(Board &b)=0;
    virtual void drop(Board &b)=0;
};

class JBlock: public AbstractBlock {
public:
    int orient;
    JBlock(Board &b);
    ~JBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);
    
};

class LBlock: public AbstractBlock {
public:
    int orient;
    LBlock(Board &b);
    ~LBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);
    
};

class SBlock: public AbstractBlock {
public:
    int orient;
    SBlock(Board &b);
    ~SBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);
    
};

class OBlock: public AbstractBlock {
public:
    OBlock(Board &b);
    ~OBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);
    
};

class ZBlock: public AbstractBlock {
public:
    int orient;
    ZBlock(Board &b);
    ~ZBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);    
};

class TBlock: public AbstractBlock {
public:
    int orient;
    TBlock(Board &b);
    ~TBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);    
};

class IBlock: public AbstractBlock {
public:
    int orient;
    IBlock(Board &b);
    ~IBlock() {}
    void show(Board &b);
    void clockwise(Board &b);
    void counterclockwise(Board &b);
    void right(Board &b);
    void left(Board &b);
    void down(Board &b);
    void drop(Board &b);
    
};

#endif
