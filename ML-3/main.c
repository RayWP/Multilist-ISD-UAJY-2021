#include "source.c" //unfreeze this if you use visual studio code
// #include "header.h" //unfreeze this if you use dev-cpp

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
    ListParent L;
    adrParent adrParent, wantToDeleteParent, beforeTheDelete;
    Tim timBaru;
    adrChild adrChild;
    Pemain pemainBaru;
    int menu;
    string namaTim, namaPelatih;
    string nama, posisi;
    string pembeli, penjual;

    createEmpty(&L);

    do
    {
        system("cls");
        showMenu();
        printf("\n[choose : ] ");
        scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            do
            {
                printf("\nNama tim: ");
                fflush(stdin);
                gets(namaTim);
            } while (strlen(namaTim) == 0);

            do
            {
                printf("\nNama pelatih: ");
                fflush(stdin);
                gets(namaPelatih);
            } while (strlen(namaPelatih) == 0);

            timBaru = makeTim(namaTim, namaPelatih);
            insertLastParent(&L, timBaru);
            break;
        case 2:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nNama pelatih: ");
                    fflush(stdin);
                    gets(namaPelatih);
                } while (strlen(namaPelatih) == 0);

                printTimByPelatih(L, namaPelatih);
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

            break;

        case 3:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\n nama pemain: ");
                    fflush(stdin);
                    gets(nama);
                    printf("\n posisi pemain: ");
                    fflush(stdin);
                    gets(posisi);
                } while (strlen(nama) == 0 || strlen(posisi) == 0);
                do
                {
                    printf("\nNama Tim: ");
                    fflush(stdin);
                    gets(namaTim);
                } while (strlen(namaTim) == 0);

                pemainBaru = makePemain(nama, posisi);
                insertFirstChildToParentTim(&L, namaTim, pemainBaru);
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

            break;

        case 4:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nnama tim yang akan mencadangkan pemain: ");
                    fflush(stdin);
                    gets(namaTim);
                } while (strlen(namaTim) == 0);
                deleteLastChild(&L, namaTim);
                break;
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

        case 5:
            printAll(L);
            break;

            // Soal bonus
        case 6:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nTim yang dibubarkan: ");
                    fflush(stdin);
                    gets(namaTim);
                } while (strlen(namaTim) == 0);
                wantToDeleteParent = findParentByNamaTim(L, namaTim);

                if (wantToDeleteParent != NULL)
                {
                    if (wantToDeleteParent == L.first)
                    {
                        deleteFirstParent(&L);
                    }
                    else
                    {
                        beforeTheDelete = findParentBeforeThisParent(L, wantToDeleteParent);
                        deleteAfterParent(&L, beforeTheDelete->tim.namaTim);
                    }
                }
                else
                {
                    printf("\n TIDAK ADA TIM SEPERTI ITU");
                }
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

            break;

        case 7:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nposisi: ");
                    fflush(stdin);
                    gets(posisi);
                } while (strlen(posisi) == 0);

                cariPemainBerdasarPosisi(L, posisi);
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

            break;

        case 8:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nNama tim pembeli: ");
                    fflush(stdin);
                    gets(pembeli);
                    printf("\nnama tim penjual: ");
                    fflush(stdin);
                    gets(penjual);
                } while (strlen(pembeli) == 0 || strlen(penjual) == 0);

                balaBantuan(&L, penjual, pembeli);
            }
            else
            {
                printf("\n\nBUAT TIM TERLEBIH DAHULU");
            }

            break;
        }
        getch();
    } while (menu != 0);
    return 0;
}
