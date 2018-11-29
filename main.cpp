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
//******************************************************************************************************************
///funkcja do zaznaczania w tablicy ju¿ istniejacych wezlow
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
        cout<<"Drzewo nie zawiera zadnych wezlow!"<<endl;
        return;
    }

///szukanie p- i jednoczesne podciaganie za soba dziadka, oraz samego rodzica:
Node *p=*root;
Node *grandpa_p=nullptr;
Node *parent_p=p;

    while(p!=nullptr&&x!=p->klucz)
    {
        /// Gdy szukany wezel jest w lewym poddrzewie:
        if(x<p->klucz)
        {
            if(p->left)     /// czy lewy wezel istnieje
            {
                grandpa_p=parent_p;
                parent_p=p;
                p=p->left;  ///przesuwam p krok dalej, wiec inne wskazniki tez musza nadazac

                if(x==p->klucz)     ///klucz znaleziony, wiec jaka rotacja jest potrzebna?
                {
                    if(grandpa_p!=parent_p)     ///klucz jest > 1 poziom oddalony od roota
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
                    }
                }
                ///skoro to nie ten wezel, to patrzymy, w ktora strone teraz...
                else if(x<p->klucz) /// czy w lewo...
                {
                    grandpa_p=parent_p;
                    parent_p=p;
                    p=p->left;
                }
                else                /// czy w prawo
                {
                    grandpa_p=parent_p;
                    parent_p=p;
                    p=p->right;
                }

            }
            else    ///nie ma lewego wezla, wiec nie ma x w drzewie
            {
                cout<<"BLAD!!! Wezla o kluczu "<<x<<" , nie ma w drzewie."<<endl;
            }

        }
        else ///czyli szukany x jest po prawej stronie drzewa
        {







        }
    }
    ///zakonczyl szukanie, ale czy znalazl???:
    if (!p)     ///jednak nie znalazl  p, wychodzimy z funkcji
    {
        cout<<"Nie udalo sie znalezc wezla o tym kluczu"<<endl<<"Nie zostal wiec usuniety..."<<endl<<endl;
        return;
    }


//dotad ok******************************************************************************************
    ///  czy p,  vel root, ma potomstwo?
    if(p==*root)                ///to powinno byc pewnikiem, tego nie trzeba sprawdzac!!!!
    {
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
            *root=p->left;
            delete p;
        }
        ///ma tylko prawe potomstwo:
        else
            *root=p->right;
            delete p;
            return;
    }
    ///***********************************************************************************************
    ///
    /// A wiec ma obu potomków i potrzeba nam poprzednika:
    ///podciagamy za soba rodzica szukanego poprzednika
    ///
    ///***********************************************************************************************
    Node* poprzednik=p->left;
    Node *rodzic_poprzednika=p;
    while(poprzednik->right)
    {
        rodzic_poprzednika=poprzednik;
        poprzednik=poprzednik->right;
    }

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

}











///funkcje przelatujace przez drzewo
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
cout<<"ok"<<endl;







        return 0;
}
