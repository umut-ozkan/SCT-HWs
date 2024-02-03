#ifndef TASTEBALANCE_H
#define TASTEBALANCE_H

class TasteBalance
{
public:
    int sweet;
    int sour;
    int bitter;
    int salty;
    int savory;
    TasteBalance(int sweet, int sour, int bitter, int salty, int savory);
    TasteBalance();
};

#endif