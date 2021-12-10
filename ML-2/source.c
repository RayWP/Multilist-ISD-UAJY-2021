#include "header.h"

void showMenu()
{
    printf("\n1. Buat server baru");
    printf("\n2. Daftar server di suatu negara");
    printf("\n3. User login");
    printf("\n4. Timeout user");
    printf("\n5. Tampilkan server seluruh dunia");
    printf("\n\n BONUS");
    printf("\n6. Refresh Server");
    printf("\n7. Cari user");
    printf("\n\n TUGAS");
    printf("\n8. Hapus User");
}

Server makeServer(string namaServer, string namaNegara)
{
    Server server;
    strcpy(server.namaServer, namaServer);
    strcpy(server.lokasiServer, namaNegara);

    return server;
}

adrParent alokasiServer(Server serverBaru)
{
    adrParent P;
    P = (adrParent)malloc(sizeof(Parent));
    P->server = serverBaru;
    P->nextParent = NULL;
    P->firstChild = NULL;
    return P;
}

void createEmpty(ListParent *L)
{
    (*L).first = NULL;
}
int isEmpty(ListParent L)
{
    if (L.first == NULL)
        return 1;
    else
        return 0;
}

void insertFirstParent(ListParent *L, Server databaru)
{
    adrParent P;
    P = alokasiServer(databaru);
    P->nextParent = (*L).first;
    (*L).first = P;
    printf("\n\nBERHASIL INSERT SERVER [first insert]");
}

void insertLastParent(ListParent *L, Server databaru)
{
    adrParent P, last;
    if (isEmpty(*L))
        insertFirstParent(&(*L), databaru);
    else
    {
        P = alokasiServer(databaru);
        last = (*L).first;
        while (last->nextParent != NULL)
        {
            last = last->nextParent;
        }
        last->nextParent = P;
        printf("\n\nBERHASIL INSERT SERVER [last insert]");
    }
}

void deleteFirstParent(ListParent *L)
{
    adrParent del;
    if (isEmpty(*L))
        printf("List kosong");
    else
    {
        del = (*L).first;
        (*L).first = (*L).first->nextParent;
        free(del);
        printf("\nDELETED SERVER PERTAMA");
    }
}

void deleteLastParent(ListParent *L)
{
    adrParent bantu, del;
    if (isEmpty(*L))
        printf("List kosong");
    else
    {
        if ((*L).first->nextParent == NULL)
        {
            deleteFirstParent(&(*L));
        }
        else
        {
            bantu = (*L).first;
            while (bantu->nextParent->nextParent != NULL)
            {
                bantu = bantu->nextParent;
            }
            del = bantu->nextParent;
            bantu->nextParent = NULL;
            free(del);
            printf("DELETED LAST SERVER");
        }
    }
}
void deleteAfterParent(ListParent *L, string namaServer)
{
    adrParent del, cari;
    cari = findParentByNamaServer((*L), namaServer);
    if (cari == NULL)
        printf("PARENT YANG DICARI TIDAK ADA");
    else
    {
        if (cari->nextParent == NULL)
            deleteLastParent(&(*L));
        else
        {
            del = cari->nextParent;
            cari->nextParent = cari->nextParent->nextParent;
            free(del);
            printf("DELETED");
        }
    }
}

adrParent findParentByNamaServer(ListParent L, string namaServer) //modified from findParent
{
    adrParent P = L.first;
    while (P != NULL)
    {
        if (strcmpi(P->server.namaServer, namaServer) != 0)
        {
            P = P->nextParent;
        }
        else
        {
            return P;
        }
    }

    return P;
}

adrParent findParentBeforeThisParent(ListParent L, adrParent target)
{
    adrParent P = L.first;
    while (P != NULL)
    {
        if (P->nextParent != target)
        {
            P = P->nextParent;
        }
        else
        {
            return P;
        }
    }

    return P;
}

void printServerByNegara(ListParent L, string namaNegara)
{
    adrParent P;
    adrChild C;
    if (isEmpty(L))
        printf("List kosong");
    else
    {
        P = L.first;
        while (P != NULL)
        {
            if (strcmpi(P->server.lokasiServer, namaNegara) == 0)
            {
                printf("\n\nKode server : %s", P->server.namaServer);
                printf("\nNegara : %s", P->server.lokasiServer);
            }
            P = P->nextParent;
        }
    }
}

User makeUser(string username, string password)
{
    User user;
    strcpy(user.username, username);
    strcpy(user.password, password);

    return user;
}

adrChild AlokasiC(User userBaru)
{
    adrChild C;
    C = (adrChild)malloc(sizeof(Child));
    C->anggota = userBaru;
    C->nextChild = NULL;
    return C;
}

void insertFirstChildToParentServer(ListParent *L, string namaServer, User userBaru)
{
    adrChild C;
    adrParent P;
    P = findParentByNamaServer((*L), namaServer);
    if (P == NULL)
        printf("Server tidak ada");
    else
    {
        C = AlokasiC(userBaru);
        C->nextChild = P->firstChild;
        P->firstChild = C;
        printf("\nBERHASIL INSERT USER %s KE SERVER %s", userBaru.username, namaServer);
    }
}

void deleteFirstChild(ListParent *L, string namaServer)
{
    adrChild del;
    adrParent P;
    P = findParentByNamaServer((*L), namaServer);
    if (P == NULL)
        printf("Server tidak ada");
    else if (!haveChild(P))
        printf("\nTidak ada anggota di server ini");
    else
    {
        del = P->firstChild;
        P->firstChild = P->firstChild->nextChild;
        free(del);
        printf("\nDELETED ANGGOTA FROM %s", namaServer);
    }
}

void deleteLastChild(ListParent *L, string namaServer)
{
    adrChild del, bantu;
    adrParent P, temp;
    P = findParentByNamaServer((*L), namaServer);
    if (P == NULL)
        printf("Server tidak ada");
    else if (!haveChild(P))
        printf("\nTIDAK ADA USER YANG LOGIN");
    else if (P->firstChild->nextChild == NULL)
        deleteFirstChild(&(*L), namaServer);
    else
    {
        bantu = P->firstChild;
        while (bantu->nextChild->nextChild != NULL)
        {
            bantu = bantu->nextChild;
        }
        del = bantu->nextChild;
        bantu->nextChild = NULL;
        free(del);
        printf("DELETED EARLIEST USER");
    }
}

int haveChild(adrParent P)
{
    if (P->firstChild != NULL)
        return 1;
    else
        return 0;
}

void printChild(adrChild C)
{
    if (C != NULL)
    {
        while (C != NULL)
        {
            printf("\n \t  User: %s", C->anggota.username);
            C = C->nextChild;
        }
    }
}

void printAll(ListParent L)
{
    adrParent P;
    adrChild C;
    if (isEmpty(L))
        printf("List kosong");
    else
    {
        P = L.first;
        while (P != NULL)
        {
            printf("\n\nKode server : %s", P->server.namaServer);
            printf("\nNegara : %s", P->server.lokasiServer);
            if (haveChild(P))
            {
                C = P->firstChild;
                printChild(C);
            }
            else
                printf("\n \t BELUM ADA USER");
            P = P->nextParent;
        }
    }
}

void cariUser(ListParent L, string username) //modifikasi dari printChild + printAll
{
    adrParent P;
    adrChild C;
    if (isEmpty(L))
        printf("List kosong");
    else
    {
        P = L.first;
        while (P != NULL)
        {
            if (haveChild(P))
            {
                C = P->firstChild;
                if (C != NULL)
                {
                    while (C != NULL)
                    {
                        if (strcmpi(C->anggota.username, username) == 0)
                        {
                            printf("\n----------");
                            printf("\nUsername: %s", C->anggota.username);
                            printf("\nPassword : %s", C->anggota.password);
                            printf("\nnegara: %s", P->server.lokasiServer);
                            return;
                        }
                        else
                        {
                            C = C->nextChild;
                        }
                    }
                }
            }
            P = P->nextParent;
        }
    }
}

// Tugas
// TODO: Revisi soal tugas(?)
void hapusUser(ListParent *L, string username) //modifikasi dari cariUser + deleteParentAfter
{
    adrParent P;
    adrChild C;
    if (isEmpty(*L))
        printf("List kosong");
    else
    {
        P = (*L).first;
        while (P != NULL)
        {
            if (haveChild(P))
            {
                C = P->firstChild;
                if (C != NULL)
                {
                    if (strcmpi(C->anggota.username, username) == 0)
                    {
                        if (C == P->firstChild)
                        {
                            deleteFirstChild(&(*L), P->server.namaServer);
                            printf("\n\nBERHASIL DELETE");
                            return;
                        }
                    }
                    else
                    {
                        while (C->nextChild != NULL)
                        {
                            if (strcmpi(C->nextChild->anggota.username, username) == 0)
                            {
                                adrChild deleted = C->nextChild;
                                C->nextChild = C->nextChild->nextChild;
                                free(deleted);
                                return;
                            } else {
                                C = C->nextChild;
                            }
                        }
                    }
                }
            }
            P = P->nextParent;
        }
    }
}