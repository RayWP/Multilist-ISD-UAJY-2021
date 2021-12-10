#include "source.c" //unfreeze this if you use visual studio code
// #include "header.h" //unfreeze this if you use dev-cpp

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
    ListParent L;
    adrParent adrParent, wantToRefreshParent, beforeTheDelete;
    Server serverBaru;
    adrChild adrChild;
    User userLogin;
    int menu;
    string namaServer, namaNegara;
    string username, password;

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
                printf("\nNama server: ");
                fflush(stdin);
                gets(namaServer);
            } while (strlen(namaServer) == 0);

            do
            {
                printf("\nNama lokasi server: ");
                fflush(stdin);
                gets(namaNegara);
            } while (strlen(namaNegara) == 0);

            serverBaru = makeServer(namaServer, namaNegara);
            insertLastParent(&L, serverBaru);
            break;
        case 2:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nNama lokasi Server: ");
                    fflush(stdin);
                    gets(namaNegara);
                } while (strlen(namaNegara) == 0);

                printServerByNegara(L, namaNegara);
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
            }

            break;

        case 3:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\n username: ");
                    fflush(stdin);
                    gets(username);
                    printf("\n password: ");
                    fflush(stdin);
                    gets(password);
                } while (strlen(username) == 0 || strlen(password) == 0);
                do
                {
                    printf("\nNama server tempat login: ");
                    fflush(stdin);
                    gets(namaServer);
                } while (strlen(namaServer) == 0);

                userLogin = makeUser(username, password);
                insertFirstChildToParentServer(&L, namaServer, userLogin);
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
            }

            break;

        case 4:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nKode server yang di-timeout: ");
                    fflush(stdin);
                    gets(namaServer);
                } while (strlen(namaServer) == 0);
                deleteLastChild(&L, namaServer);
                break;
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
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
                    printf("\nKode server yang dibubarkan: ");
                    fflush(stdin);
                    gets(namaServer);
                } while (strlen(namaServer) == 0);
                wantToRefreshParent = findParentByNamaServer(L, namaServer);

                if (wantToRefreshParent != NULL)
                {
                    while (haveChild(wantToRefreshParent))
                    {
                        deleteFirstChild(&L, wantToRefreshParent->server.namaServer);
                    }
                    printf("\n\n SERVER REFRESHED");
                }
                else
                {
                    printf("\n TIDAK ADA SERVER SEPERTI ITU");
                }
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
            }

            break;

        case 7:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nUsername: ");
                    fflush(stdin);
                    gets(username);
                } while (strlen(username) == 0);

                cariUser(L, username);
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
            }

            break;

        case 8:
            if (!isEmpty(L))
            {
                do
                {
                    printf("\nUsername yang akan dihapus: ");
                    fflush(stdin);
                    gets(username);
                } while (strlen(username) == 0);
                hapusUser(&L, username);
            }
            else
            {
                printf("\n\nBUAT SERVER TERLEBIH DAHULU");
            }

            break;
        }
        getch();
    } while (menu != 0);
    return 0;
}
