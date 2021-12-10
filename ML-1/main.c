#include "source.c" //unfreeze this if you use visual studio code
// #include "header.h" //unfreeze this if you use dev-cpp

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
    ListParent L;
    adrParent adrParent, wantToDeleteParent, beforeTheDelete;
    Cabang cabangBaru;
    adrChild adrChild;
    Anggota anggotaBaru;
    int menu;
    string kodeCabang, namaNegara;
    string kodeCabangPemberi, kodeCabangPenerima;
    string id, nama;

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
                printf("\nKode cabang: ");
                fflush(stdin);
                gets(kodeCabang);
            } while (strlen(kodeCabang) == 0);

            do
            {
                printf("\nNama negara: ");
                fflush(stdin);
                gets(namaNegara);
            } while (strlen(namaNegara) == 0);

            cabangBaru = makeCabang(kodeCabang, namaNegara);
            insertLastParent(&L, cabangBaru);
            break;
        case 2:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nNama negara: ");
                    fflush(stdin);
                    gets(namaNegara);
                } while (strlen(namaNegara) == 0);

                printCabangByNegara(L, namaNegara);
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
            }

            break;

        case 3:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nKode cabang yang ditambahkan anggotanya: ");
                    fflush(stdin);
                    gets(kodeCabang);
                } while (strlen(kodeCabang) == 0);
                do
                {
                    printf("\n id anggota: ");
                    fflush(stdin);
                    gets(id);
                    printf("\n nama anggota: ");
                    fflush(stdin);
                    gets(nama);
                } while (strlen(id) == 0 || strlen(nama) == 0);

                anggotaBaru = makeAnggota(id, nama);
                insertFirstChildToParentCabang(&L, kodeCabang, anggotaBaru);
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
            }

            break;

        case 4:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nKode cabang yang dihapus anggotanya: ");
                    fflush(stdin);
                    gets(kodeCabang);
                } while (strlen(kodeCabang) == 0);
                deleteFirstChild(&L, kodeCabang);
                break;
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
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
                    printf("\nKode cabang yang dibubarkan: ");
                    fflush(stdin);
                    gets(kodeCabang);
                } while (strlen(kodeCabang) == 0);
                wantToDeleteParent = findParentByKodeCabang(L, kodeCabang);

                if (wantToDeleteParent != NULL)
                {
                    if (wantToDeleteParent == L.first)
                    {
                        deleteFirstParent(&L);
                    }
                    else
                    {
                        beforeTheDelete = findParentBeforeThisParent(L, wantToDeleteParent);
                        deleteAfterParent(&L, beforeTheDelete->cabang.kodeCabang);
                    }
                }
                else
                {
                    printf("\n TIDAK ADA CABANG SEPERTI ITU");
                }
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
            }

            break;

        case 7:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nid anggota: ");
                    fflush(stdin);
                    gets(id);
                } while (strlen(id) == 0);

                lacakAgent(L, id);
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
            }

            break;

        case 8:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nKode cabang yang memberikan: ");
                    fflush(stdin);
                    gets(kodeCabangPemberi);
                    printf("\nKode cabang yang menerima: ");
                    fflush(stdin);
                    gets(kodeCabangPenerima);
                } while (strlen(kodeCabangPemberi) == 0 || strlen(kodeCabangPenerima) == 0);

                balaBantuan(&L, kodeCabangPemberi,kodeCabangPenerima);
            }
            else
            {
                printf("\n\nBUAT CABANG TERLEBIH DAHULU");
            }

            break;
        }
        getch();
    } while (menu != 0);
    return 0;
}
