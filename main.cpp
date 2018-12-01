#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>

using namespace std;

int licznik=0;
int k;
bool tab[29976]{};
struct Node
{
    int klucz;
    char ch[16]{};
    Node *right;
    Node *left;

};
void preorder(Node *root)
{
    if(root)
    {
        cout<<root->klucz<<" "<<"zawartosc jego tablicy: ";
            for(int i=0; i<16; i++)
            {
                if(root->ch[i])
                cout<<root->ch[i];
            }
            cout<<endl;
            licznik++;
        preorder(root->left);
        preorder(root->right);
    }
    return;
}

void szukanie_pre_grand(Node * grand, Node **pre_grand, Node * root)
{
*pre_grand=nullptr; //to rodzic p, ktory sie przyda, gdy trzeba bedzie podpiac poprzednika w miejsce p
Node *dziad=root;        //wskaznik wedrujacy p
int k=grand->klucz;
cout<<"Rozpoczynam szukanie wezla o kluczu dziadka: "<<grand->klucz<<endl;

    while(k!=dziad->klucz)      //rob to, co w petli, az bedzie sukces lub sciana
    {
        *pre_grand=dziad;
        if(dziad->klucz<k)
            dziad=dziad->right;
        else
            dziad=dziad->left;
    }
    ///zakonczyl szukanie, ale czy znalazl???:
    if (!dziad)     //jednak nie znalazl  p, wychodzimy z funkcji
    {
        cout<<"Nie udalo sie znalezc wezla o tym kluczu"<<endl<<"Nie zostal wiec usuniety..."<<endl<<endl;
        return;
    }
    ///jadnak znalazl dziada, a jego rodzic to pre_grand
}
///**************************************************************************************************************

///     BLOK FUNKCJI ROTUJACYCH

///**************************************************************************************************************
void rotacja_R(Node ** parent)  ///ok dla rodzic==root
{

    Node * x=(*parent)->left;
    (*parent)->left=x->right;
    x->right=*parent;
    *parent=x;
}

void rotacja_RR(Node ** grand, Node *root)
{
    /*
    Node *pre_grandpa_p=nullptr;
    if(*grand!=root)///znajdowanie pradziadka
    {
        szukanie_pre_grand(*grand, &pre_grandpa_p, root);
        //cout<<"pradziadek wezla o kluczu "<<p->klucz<<" to "<<pre_grandpa_p->klucz<<endl;
        ///mamy pradziadka naszego wezla!!!!!!!!!
    }
    else
    {
        ///pre_grandpa_p=*grand;
    }
    */
    Node * x=(*grand)->left;
    (*grand)->left=x->right;
    x->right=*grand;
    *grand=x;
}

void rotacja_LR(Node ** grand, Node ** parent, Node ** p)
{

}

void rotacja_L(Node ** parent)  ///chyba ok dla rodzic==root
{
    Node * x=(*parent)->right;
    (*parent)->right=x->left;
    x->left=*parent;
    *parent=x;
}
void rotacja_LL(Node ** grand, Node** parent, Node ** p)
{

}

void rotacja_RL(Node ** grand, Node ** parent, Node ** p)
{

}
///********************************************************************************************************
//*********************************************************************************************************
///funkcja do zaznaczania w tablicy juz istniejacych wezlow
    void inorder_stan(Node *root, bool *a)///gotowa
{
         if(root)
        {
            inorder_stan(root->left, a);        ///rekurencyjnie w porzadku poprzecznym przechodzi drzewo
                                                ///i wracajac zaznacza w przekazanej tablicy wystapienia
            a[root->klucz-25]=true;             ///kluczy w odwiedzonych wezlach
            inorder_stan(root->right, a);
        }

    return;
}
//********************************************************************************************************
int wstawienie(Node **root, int klucz)///gotowa do sprawdzenia oprócz tablicy
{
///zaczynamy szukac miejsca na nowy wezel
        Node *p=*root;
        Node *rodzic=nullptr;
        if(*root)
        {
            while(p!=nullptr)
            {
                if(p->klucz==klucz) /// obsluga przypadku powtorzenia wstawianego klucza
                {
                    cout<<"BLAD! W drzewie jest juz wezel o kluczu = "<<klucz<<endl<<endl;
                    return 1;
                }
                rodzic=p;
                if(p->klucz>klucz)
                    p=p->left;
                else
                    p=p->right;        ///znajdujemy miejsce na stworzenie naszego wezla-liscia
            }
        }
///alokacja pamieci na nowy wezel listy
        Node *nowy= new Node;
        if(!nowy)
        {
            cout<<"Nie udalo sie utworzyc nowego wezla drzewa!\n Brak pamieci!"<<std::endl;
            return -1;                  ///gdy brak pamieci na wezel
        }

///inicjalizacja liczbowych zmiennych wezla:
        nowy->klucz=klucz;

        ///potrzeba jeszcze wypelnic skladowa tablice wezla....
        for(int i=0; i<16; i++)
        {
            nowy->ch[i]=(rand()%23)+65;
        }
        nowy->right=nullptr;
        nowy->left=nullptr;

        if(!*root)
        {
            *root=nowy;
            return 0;
        }
/// podczepienie naszego wezla pod rodzica:
        else if(rodzic->klucz>klucz)
            rodzic->left=nowy;
        else
            rodzic->right=nowy;
        return 0;
}

//***********************************************************************************************************
void wstawienie_X_elementow(Node **root, int X)///gotowa
{
    int los;
    bool tabl_losowych[29976];
    srand(time(0));

    ///przejscie przez drzewo aby zaktualizowac tablice wystepujacych juz w drzewie kluczzy
    inorder_stan(*root, tabl_losowych);

    ///proces wstawiania wezla:
        for(int i=0; i<X; i++)
        {
            ///losowanie unikalnej liczby i przeslanie jej do wezla listy
            do
            {
                los=(rand()%29976);
            }
            while(tabl_losowych[los]);
            tabl_losowych[los]=true;        ///zapamietanie wylosowania danej liczb

            ///wywolanie funkcji wstawiajacej dla wylosowanego klucza
            wstawienie(root, los+25);
        }
        return;
}
//****************************************************************************************************************
void szukaj(Node *root, int szukany)///gotowa
{
    //int sukces=0;
    if(!root)
    {
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
        return;
    }
    Node *p=root;
    while(p!=nullptr)
    {
        if(p->klucz==szukany)
        {
            cout<<"Znaleziono szukany klucz "<<szukany<<endl;
            cout<<"Oto zawartosc jego tablicy: ";

            for(int i=0; i<16; i++)
            {
                if(p->ch[i])
                cout<<p->ch[i];
            }
            //sukces=1;
            return;
        }
        else
        {
            if(p->klucz<szukany)
                p=p->right;
            else
                p=p->left;
        }
    }
    //if(!sukces)     ///to chyba niepotrzebne
        cout<<"Nie znaleziono wezla o kluczu = "<<szukany<<endl<<endl;

    return;
}
//********************************************************************************************************************
void usuwanie(Node **root, int x)
{

cout<<"Rozpoczynam usuwanie wezla o kluczu: "<<x<<endl;

///sprawdzenie istnienia drzewa:
    if(!*root)
    {
        cout<<"Drzewo nie zawiera zadnych wezlow!, usuwanie nieudane"<<endl;
        return;
    }

///szukanie p- i jednoczesne podciaganie za soba dziadka, oraz samego rodzica:

cout<<"przed whilem"<<endl;
Node *p=nullptr;
///duza petla while: szuka, znajduje, rotuje az do korzenia
///while(x!=(*root)->klucz) ///lub p!=root
///{
    p=*root;
    Node *grandpa_p=nullptr;
    Node *parent_p=p;

    int licznik_while=0;
    while(p!=nullptr&&x!=p->klucz)
    {
        licznik_while++;
        cout<<"wchodzimy do while "<<licznik_while<<" raz"<<endl;
        /// Gdy szukany wezel jest w lewym poddrzewie:
        if(x<p->klucz)
        {
            cout<<"jestem w lewym poddrzewie"<<endl;
            if(p->left)     /// czy lewy wezel istnieje
            {
                cout<<"lewy wezel istnieje"<<endl;
                grandpa_p=parent_p;
                parent_p=p;
                p=p->left;  ///przesuwam p krok dalej, wiec inne wskazniki tez musza nadazac

                if(x==p->klucz)     ///klucz znaleziony, wiec jaka rotacja jest potrzebna?
                {
                    cout<<"pierwszy lewy wezel i jest klucz"<<endl;
                    break;
                    /*if(grandpa_p!=parent_p)     ///klucz jest > 1 poziom oddalony od roota
                    {
                        if(grandpa_p->left==parent_p)
                        {
                            ///rotacja podwójna homo lewa
                            cout<<"Rotacja podwojna homo lewa"<<endl;
                        }
                        else
                        {
                            ///rotacja podwójna hetero prawa rodzica, potem lewa p
                            cout<<"Rotacja podwojna hetero prawa rodzica, potem lewa p"<<endl;
                        }
                    }
                    else
                    {
                        ///rotacja pojedyncza prawa
                        cout<<"Rotacja pojedyncza prawa"<<endl;
                    }*/
                }
                ///skoro to nie ten wezel, to patrzymy, w ktora strone teraz...
                else if(x<p->klucz) /// czy w lewo...
                {
                    cout<<"wybor lewej drogi do drugiego wezla"<<endl;
                    grandpa_p=parent_p;
                    parent_p=p;
                    p=p->left;
                }
                else                /// czy w prawo
                {
                    cout<<"wybor prawej drogi do drugiego wezla"<<endl;
                    grandpa_p=parent_p;
                    parent_p=p;
                    p=p->right;
                }

            }
            else    ///nie ma lewego wezla, wiec nie ma x w drzewie
            {
                cout<<"BLAD!!! Wezla o kluczu "<<x<<" , nie ma w drzewie."<<endl;
                p=nullptr;
                return;
            }

        }
        else ///czyli szukany x jest po prawej stronie drzewa
        {
            cout<<"wejscie w prawe niedokonczone poddrzewo"<<endl;

        }
    }
    ///zakonczyl szukanie, ale czy znalazl???:
    if (!p)     ///jednak nie znalazl  p, wychodzimy z funkcji
    {
        cout<<"Nie udalo sie znalezc wezla o tym kluczu"<<endl<<"Nie zostal wiec usuniety..."<<endl<<endl;
        return;
    }


///********************************************************************************************************
    /// Obsluga wszystkich rotacji dla lewego i prawego drzewa:
///********************************************************************************************************
cout<<"przed obsluga rotacji"<<endl;
cout<<"root "<<(*root)->klucz<<" root left "<<(*root)->left->klucz<<" grand "<<grandpa_p->klucz<<" rodzic "<<parent_p->klucz<<endl;

cout<<"wew obslugi rotacji"<<endl;
///*****************************************************************************************************************
///obsluga pojedynczych rotacji:
///*****************************************************************************************************************
    if(parent_p==*root)   /// rodzic=dziadek to root, wiec wystarczy pojedyncza rotacja w lewo lub w prawo
    {
        if(x<(*root)->klucz)
        {
            ///rotacja pojedyncza w prawo zrobiona do końca
            cout<<"Rotacja pojedyncza w prawo"<<endl;
            rotacja_R(&parent_p);
            *root=parent_p;
            cout<<"root po rotacji "<<(*root)->klucz<<p->klucz<<endl;
            preorder(*root);///do usuniecia
        }
        else
        {
            /// rotacja pojedyncza w lewo
            cout<<"Rotacja pojedyncza w lewo"<<endl;
            rotacja_L(&parent_p);
            *root=parent_p;
            cout<<"root po rotacji "<<(*root)->klucz<<p->klucz<<endl;
            preorder(*root);///do usuniecia
        }
    }
///***************************************************************************************************************
/// gdy po podwojnej rotacji zmieni sie root
///***************************************************************************************************************
        else if(grandpa_p==*root)
        {
            if(grandpa_p->left==parent_p)
            {
                if(parent_p->left==p)   /// jednorodna
                {
                    ///rotacja podwojna w prawo rodzic w prawo p
                    cout<<"Rotacja podwojna w prawo"<<endl;
                    rotacja_RR(&grandpa_p, *root);
                }
                else    /// niejednorodna
                {
                    ///rotacja podwojna w lewo p i w prawo p
                }
            }
            else    /// jesli grandpa_p->right==p
            {
                //if((*root)->left->left==p){rotacja_RR(&grandpa_p);*root=grandpa_p;}
                if(parent_p->right==p) ///jednorodna
                {
                    ///rotacja podwojna w lewo rodzic w lewo p
                }
                else    ///     niejednorodna
                {
                    ///rotacja podwojna w prawo p w lewo p
                }
            }
        }
///***********************************************************************************************************************
///przypadek, gdy wskutek rotacji nie zmieni sie root:
///***********************************************************************************************************************
        else
        {
            if(grandpa_p->left==parent_p)
            {
                if(parent_p->left==p)   /// jednorodna
                {
                    ///rotacja podwojna w prawo rodzic w prawo p
                    cout<<"Rotacja podwojna w prawo"<<endl;

                    rotacja_RR(&grandpa_p, *root);
                }
                else    /// niejednorodna
                {
                    ///rotacja poswojna w lewo p i w prawo p
                }
            }
            else    /// jesli grandpa_p->right==p
            {
                //if((*root)->left->left==p){rotacja_RR(&grandpa_p);*root=grandpa_p;}
                if(parent_p->right==p) ///jednorodna
                {
                    ///rotacja podwojna w lewo rodzic w lewo p
                }
                else    ///     niejednorodna
                {
                    ///rotacja podwojna w prawo p w lewo p
                }
            }
        }

///cout<<"przed rotacja "<<endl;
///cout<<"root "<<(*root)->klucz<<" root left "<<(*root)->left->klucz<<" grand "<<grandpa_p->klucz<<" rodzic "<<parent_p->klucz<<endl;
///cout<<"po rotacji"<<endl;
/// cout<<"root "<<(*root)->klucz<<" root left "<<(*root)->left->klucz<<" grand "<<grandpa_p->klucz<<" rodzic "<<parent_p->klucz<<endl;
///cout<<" root left left "<<(*root)->left->left->klucz<<endl;
///" root left left "<<(*root)->left->left->klucz<<
            cout<<"root po rotacji "<<(*root)->klucz<<endl;
            preorder(*root);///do usuniecia
































/*
cout<<"wezel znaleziony"<<endl;
//dotad ok******************************************************************************************
    ///  czy p,  vel root, ma potomstwo?
    if(p==*root)                ///to powinno byc pewnikiem, tego nie trzeba sprawdzac!!!!
    {
        cout<<"jestem w szukaniu poprzednika"<<endl;
        //p=*root;
        /// Gdy root nie ma potomkow:
        if(p->left==nullptr&&p->right==nullptr)
        {
            *root=nullptr;          ///zerujemy roota
            delete p;               ///zwalniamy pamiec po p
            cout<<"Wezel usuniety..."<<endl<<endl;
            return;
        }
        ///ma tylko lewe poddrzewo:
        else if(!p->right)
        {
            cout<<"ma tylko lewe poddrzewo"<<endl;
            *root=p->left;
            delete p;
        }
        ///ma tylko prawe potomstwo:
        else if(!p->left)
        {
            cout<<"ma tylko lewe poddrzewo"<<endl;
            *root=p->right;
            delete p;
            return;
        }
    }
    ///***********************************************************************************************
    ///
    /// A wiec ma obu potomków i potrzeba nam poprzednika:
    ///podciagamy za soba rodzica szukanego poprzednika
    ///
    ///***********************************************************************************************
    //p=*root;
    cout<<"przed wyszukiwaniem poprzednika"<<endl;
    Node* poprzednik=p->left;
    Node *rodzic_poprzednika=p;
    cout<<"przed whilem w szukaniu poprzednika"<<endl;
    while(poprzednik->right)
    {
        rodzic_poprzednika=poprzednik;
        poprzednik=poprzednik->right;
    }
cout<<"poprzednik "<<poprzednik->klucz<<endl;
    ///mamy poprzednika, teraz go obejrzymy i wytniemy...

    if(poprzednik==p->left) ///gdy poprzednik jest tuz obok p, po lewej stronie,
    {
        *root=p->left;
        (*root)->right=p->right;
        delete p;
        return;
    }
    else
    {
    ///gdy poprzednik jest gdzies na koncu...

    ///wyluskanie poprzednika:
        rodzic_poprzednika->right=poprzednik->left;
        poprzednik->left=nullptr;

    /// wstawienie poprzednika:
        poprzednik->left=(*root)->left;
        poprzednik->right=(*root)->right;
        *root=poprzednik;
        delete p;

    return;
    }
    */

}











///funkcje przelatujace przez drzewo

void preorder_licz(Node *root)
{
    licznik=0;
    cout<<"Wyswietlanie w trybie preorder: "<<endl;
    preorder(root);
    cout<<endl<<"licznik preorder = "<<licznik<<endl;
    if(!licznik)
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
}
///zwykla funkcja inorder
void inorder(Node *root)
{
         if(root)
        {
            inorder(root->left);
            cout<<root->klucz<<" "<<"zawartosc jego tablicy: ";
            for(int i=0; i<16; i++)
            {
                if(root->ch[i])
                cout<<root->ch[i];
            }
            cout<<endl;
            licznik++;
            inorder(root->right);
        }
    return;
}

///funkcja inorder do zliczania odwiedzonych wezlow
void inorder_licz(Node *root)
{
    licznik=0;
    cout<<"Wyswietlanie w trybie inorder: "<<endl;
    inorder(root);
    cout<<endl<<"licznik inorder = "<<licznik<<endl;
    if(!licznik&&!root) ///dodalem dodatkowy warunek sprawdzajacy
        cout<<"Drzewo nie zawiera zadnych elementow!"<<endl<<endl;
}




int main()
{
    srand(time(0));

Node *drzewo=nullptr;

wstawienie(&drzewo, 100);
wstawienie(&drzewo, 50);
wstawienie(&drzewo, 40);
wstawienie(&drzewo, 30);
wstawienie(&drzewo, 20);
wstawienie(&drzewo, 200);
wstawienie(&drzewo, 60);
//szukaj(drzewo, 30);
//szukaj(drzewo, 35);

//usuwanie(&drzewo, 50);
//preorder_licz(drzewo);


usuwanie(&drzewo, 40);
preorder_licz(drzewo);
cout<<"root"<<drzewo->klucz<<endl;
cout<<"ok"<<endl;







        return 0;
}
