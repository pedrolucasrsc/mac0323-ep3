#ifndef ARVORE23_H
#define ARVORE23_H

template <class Key, class Item>
class No23
{
    public:
        Key chave1;
        Item valor1;
        Key chave2;
        Item valor2;
        No23<Key,Item> *ap1 = nullptr;
        No23<Key,Item> *ap2 = nullptr;
        No23<Key,Item> *ap3 = nullptr;
        bool eh2no = true;
        int tamsub = 1;
        No23() {};
        ~No23() {};
        No23(Key key,Item val) {chave1 = key; valor1 = val;};
};

template <class Key, class Item>
class TsA23
{
    private:
        No23<Key,Item> *raiz = nullptr;
        No23<Key,Item> * put23(No23<Key,Item> *,Key,Item,bool *);
        int size(No23<Key,Item> *);
        bool ehFolha(No23<Key,Item> *a) {return a->ap1 == nullptr;};
        void vira2no(No23<Key,Item> *a) {a->ap3 = nullptr; a->eh2no = true; a->chave2 = Key(); a->valor2 = Item();};
        bool checaTrocaValor(No23<Key,Item> *,Key,Item,bool);
        Item get(No23<Key,Item> *,Key);
        int rank(No23<Key,Item> *,Key);
        Key select(No23<Key,Item> *,int);
    public:
        void add(Key,Item);
        Item value(Key);
        int rank(Key);
        Key select(int);
        bool isIn(Key);
        int size() {return size(raiz);};
        TsA23() {};
        ~TsA23() {};
};

template <class Key, class Item>
bool TsA23<Key,Item>::isIn(Key key) {
  return key == select(rank(key));
}

template <class Key, class Item>
bool TsA23<Key,Item>::checaTrocaValor(No23<Key,Item> *a, Key key, Item val, bool eh2no) {
    if (key == a->chave1) {
        a->valor1 = val;
        return true;
    }
    else if (!a->eh2no && key == a->chave2) {
        a->valor2 = val;
        return true;
    }
    return false;
}

template <class Key, class Item>
int TsA23<Key,Item>::size(No23<Key,Item> *a) {
    if (a == nullptr) return 0;
    return a->tamsub;
}

template <class Key, class Item>
void TsA23<Key,Item>::add(Key key, Item val) {
    bool c = false;
    raiz = put23(raiz,key,val,&c);
    return;
}

template <class Key, class Item>
No23<Key,Item> * TsA23<Key,Item>::put23(No23<Key,Item> *a, Key key, Item val, bool *cresceu) {
    // caso especial: raiz == nullptr
    if (a == nullptr) {
        a = new No23<Key,Item>(key,val);
        return a;
    }
    bool eh2no = a->eh2no;
    // verificar se chave já está lá
    if (checaTrocaValor(a,key,val,eh2no)) {
        *cresceu = false;
        return a;
    }
    // inserimos em folha
    if (ehFolha(a)) {
        // caso fácil
        if (eh2no) {
            *cresceu = false;
            // colocar lá
            if (key < a->chave1) {
                a->chave2 = a->chave1;
                a->valor2 = a->valor1;
                a->chave1 = key;
                a->valor1 = val;
            }
            else {
                a->chave2 = key;
                a->valor2 = val;
            }
            a->eh2no = false;
            a->tamsub = size(a->ap1) + size(a->ap2) + size(a->ap3) + 2;
            return a;
        }
        else { /* a é 3 no */
            // ocorrerá split
            *cresceu = true;
            No23<Key,Item> * alfa = new No23<Key,Item>(); // receberá menor
            No23<Key,Item> * beta = new No23<Key,Item>(); // receberá maior
            if (key < a->chave1) {
                alfa->chave1 = key;
                alfa->valor1 = val;
                beta->chave1 = a->chave2;
                beta->valor1 = a->valor2;
            }
            else if (a->chave2 < key) {
                alfa->chave1 = a->chave1;
                alfa->valor1 = a->valor1;
                beta->chave1 = key;
                beta->valor1 = val;
                a->chave1 = a->chave2;
                a->valor1 = a->valor2;
            }
            else {
                alfa->chave1 = a->chave1;
                alfa->valor1 = a->valor1;
                beta->chave1 = a->chave2;
                beta->valor1 = a->valor2;
                a->chave1 = key;
                a->valor1 = val;
            }
            vira2no(a);
            a->ap1 = alfa;
            a->ap2 = beta;
            a->tamsub = size(a->ap1) + size(a->ap2) + 1;
            return a;
        }
    }
    // a não é folha
    if (key < a->chave1) {
        No23<Key,Item> *alfa = put23(a->ap1,key,val,cresceu);
        if (*cresceu) {
            if (eh2no) { /* tem espaço =) */
                a->eh2no = false;
                a->chave2 = a->chave1;
                a->valor2 = a->valor1;
                a->ap3 = a->ap2;
                a->chave1 = alfa->chave1;
                a->valor1 = alfa->valor1;
                a->ap1 = alfa->ap1;
                a->ap2 = alfa->ap2;
                *cresceu = false;
                delete alfa;
            }
            else { /* é 3 nó =( */
                No23<Key,Item> *beta = new No23<Key,Item>();
                beta->chave1 = a->chave2;
                beta->valor1 = a->valor2;
                beta->ap1 = a->ap2;
                beta->ap2 = a->ap3;
                a->ap1 = alfa;
                a->ap2 = beta;
                beta->tamsub = size(beta->ap1) + size(beta->ap2) + 1;
                vira2no(a);
            }  
        }
        if (a->eh2no)
            a->tamsub = size(a->ap1) + size(a->ap2) + 1;
        else
            a->tamsub = size(a->ap1) + size(a->ap2) + size(a->ap3) + 2;
        return a;
    }
    if (a->eh2no) { // a->chave1 < key
        No23<Key,Item> *beta = put23(a->ap2,key,val,cresceu);
        if (*cresceu) {
            // tem espaço
            a->chave2 = beta->chave1;
            a->valor2 = beta->valor1;
            a->ap2 = beta->ap1;
            a->ap3 = beta->ap2;
            a->eh2no = false;
            a->tamsub = size(a->ap1) + size(a->ap2) + size(a->ap3) + 2;
            *cresceu = false;
            delete beta;
        }
        else
            a->tamsub = size(a->ap1) + size(a->ap2) + 1;
        return a;
    }
    else { // é 3 nó precisa saber se coloca em ap2 ou ap3
        if (a->chave2 < key) {
            No23<Key,Item> *beta = put23(a->ap3,key,val,cresceu);
            if (*cresceu) {
                No23<Key,Item> *alfa = new No23<Key,Item>();
                alfa->chave1 = a->chave1;
                alfa->valor1 = a->valor1;
                alfa->ap1 = a->ap1;
                alfa->ap2 = a->ap2;
                alfa->tamsub = size(alfa->ap1) + size(alfa->ap2) + 1;
                a->chave1 = a->chave2;
                a->valor1 = a->valor2;
                a->ap1 = alfa;
                a->ap2 = beta;
                a->tamsub = size(a->ap1) + size(a->ap2) + 1;
                vira2no(a);
            }
            else
                a->tamsub = size(a->ap1) + size(a->ap2) + size(a->ap3) + 2;
            return a;
        }
        else { // chave1 < key < chave2
            No23<Key,Item> *gama = put23(a->ap2,key,val,cresceu);
            if (*cresceu) {
                No23<Key,Item> *beta = new No23<Key,Item>();
                beta->chave1 = a->chave2;
                beta->valor1 = a->valor2;
                beta->ap1 = gama->ap2;
                beta->ap2 = a->ap3;
                beta->tamsub = size(beta->ap1) + size(beta->ap2) + 1;
                a->ap2 = gama->ap1;
                a->tamsub = size(a->ap1) + size(a->ap2) + 1;
                vira2no(a);
                gama->ap1 = a;
                gama->ap2 = beta;
                gama->tamsub = size(gama->ap1) + size(gama->ap2) + 1;
                return gama;
            }
            else
                a->tamsub = size(a->ap1) + size(a->ap2) + size(a->ap3) + 2;
            return a;
        }
    }
}

template <class Key, class Item>
Item TsA23<Key,Item>::value(Key key) {
    return get(raiz,key);
}

template <class Key, class Item>
Item TsA23<Key,Item>::get(No23<Key,Item> *a, Key key) {
    if (a == nullptr) return Item();
    if (key < a->chave1)
        return get(a->ap1,key);
    if (a->chave1 < key) {
        if (a->eh2no)
            return get(a->ap2,key);
        else {
            if (key < a->chave2)
                return get(a->ap2,key);
            if (a->chave2 < key)
                return get(a->ap3,key);
            return a->valor2;
        }
    }
    return a->valor1;
}

template <class Key, class Item>
int TsA23<Key,Item>::rank(Key key) {
    return rank(raiz,key);
}

template <class Key, class Item>
int TsA23<Key,Item>::rank(No23<Key,Item> *a, Key key) {
    if (a == nullptr) return 0;
    if (key < a->chave1)
        return rank(a->ap1,key);
    if (a->chave1 < key) {
        if (a->eh2no)
            return size(a->ap1) + 1 + rank(a->ap2,key);
        else {
            if (key < a->chave2)
                return size(a->ap1) + 1 + rank(a->ap2,key);
            if (a->chave2 < key)
                return size(a->ap1) + size(a->ap2) + 2 + rank(a->ap3,key);
            // key == a->chave2
            return size(a->ap1) + size(a->ap2) + 1;
        }
    }
    // key == a->chave1
    return size(a->ap1);
}

template <class Key, class Item>
Key TsA23<Key,Item>::select(int k) {
    return select(raiz,k);
}

template <class Key, class Item>
Key TsA23<Key,Item>::select(No23<Key,Item> *a, int k) {
    if (a == nullptr) return Key();
    int t1 = size(a->ap1);
    if (k == t1)
        return a->chave1;
    else if (k < t1)
        return select(a->ap1,k);
    else {
        if (a->eh2no)
            return select(a->ap2,k-t1-1);
        else {
            int t2 = size(a->ap1) + size(a->ap2) + 1;
            if (k == t2)
                return a->chave2;
            else if (k < t2)
                return select(a->ap2,k-t1-1);
            else // t2 < k
                return select(a->ap3,k-t2-1);
        }
    }
}

#endif
