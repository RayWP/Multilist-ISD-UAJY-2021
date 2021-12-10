#include "header.h"

void showMenu()
{
    printf("\n1. Buat tim baru");
    printf("\n2. Cari tim berdasar pelatih");
    printf("\n3. Tambah pemain baru");
    printf("\n4. Cadangkan pemain");
    printf("\n5. Tampilkan seluruh liga");
    printf("\n\n BONUS");
    printf("\n6. Gugurkan tim");
    printf("\n7. Cari pemain berdasar posisi");
    printf("\n\n TUGAS");
    printf("\n8. Bursa transfer");
}

Tim makeTim(string namaTim, string namaPelatih)
{
    Tim tim;
    strcpy(tim.namaTim, namaTim);
    strcpy(tim.namaPelatih, namaPelatih);

    return tim;
}

adrParent alokasiTim(Tim timBaru)
{
    adrParent P;
    P = (adrParent)malloc(sizeof(Parent));
    P->tim = timBaru;
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

void insertFirstParent(ListParent *L, Tim databaru)
{
    adrParent P;
    P = alokasiTim(databaru);
    P->nextParent = (*L).first;
    (*L).first = P;
    printf("\n\nBERHASIL INSERT tim [first insert]");
}

void insertLastParent(ListParent *L, Tim databaru)
{
    adrParent P, last;
    if (isEmpty(*L))
        insertFirstParent(&(*L), databaru);
    else
    {
        P = alokasiTim(databaru);
        last = (*L).first;
        while (last->nextParent != NULL)
        {
            last = last->nextParent;
        }
        last->nextParent = P;
        printf("\n\nBERHASIL INSERT tim [last insert]");
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
        printf("\nDELETED TIM PERTAMA");
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
            printf("DELETED LAST TIM");
        }
    }
}
void deleteAfterParent(ListParent *L, string namaTim)
{
    adrParent del, cari;
    cari = findParentByNamaTim((*L), namaTim);
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

adrParent findParentByNamaTim(ListParent L, string namaTim) //modified from findParent
{
    adrParent P = L.first;
    while (P != NULL)
    {
        if (strcmpi(P->tim.namaTim, namaTim) != 0)
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

void printTimByPelatih(ListParent L, string namaPelatih)
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
            if (strcmpi(P->tim.namaPelatih, namaPelatih) == 0)
            {
                printf("\n\nNama Tim : %s", P->tim.namaTim);
                printf("\nNama pelatih : %s", P->tim.namaPelatih);
            }
            P = P->nextParent;
        }
    }
}

Pemain makePemain(string nama, string posisi)
{
    Pemain pemain;
    strcpy(pemain.nama, nama);
    strcpy(pemain.posisi, posisi);

    return pemain;
}

adrChild AlokasiC(Pemain anggotaBaru)
{
    adrChild C;
    C = (adrChild)malloc(sizeof(Child));
    C->pemain = anggotaBaru;
    C->nextChild = NULL;
    return C;
}

void insertFirstChildToParentTim(ListParent *L, string namaTim, Pemain anggotaBaru)
{
    adrChild C;
    adrParent P;
    P = findParentByNamaTim((*L), namaTim);
    if (P == NULL)
        printf("Tim tidak ada");
    else
    {
        C = AlokasiC(anggotaBaru);
        C->nextChild = P->firstChild;
        P->firstChild = C;
        printf("\nBERHASIL INSERT");
    }
}

void deleteFirstChild(ListParent *L, string namaTim)
{
    adrChild del;
    adrParent P;
    P = findParentByNamaTim((*L), namaTim);
    if (P == NULL)
        printf("Tim tidak ada");
    else if (!haveChild(P))
        printf("\nTidak ada pemain di tim ini");
    else
    {
        del = P->firstChild;
        P->firstChild = P->firstChild->nextChild;
        free(del);
        printf("DELETED ANGGOTA FROM %s", namaTim);
    }
}

void deleteLastChild(ListParent *L, string namaTim)
{
    adrChild del, bantu;
    adrParent P, temp;
    P = findParentByNamaTim((*L), namaTim);
    if (P == NULL)
        printf("Tim tidak ada");
    else if (!haveChild(P))
        printf("\nTIDAK ADA PEMAIN DI TIM INI");
    else if (P->firstChild->nextChild == NULL)
        deleteFirstChild(&(*L), namaTim);
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
        printf("DELETED PEMAIN");
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
            printf("\n \t %s, %s", C->pemain.nama, C->pemain.posisi);
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
            printf("\n\nNama Tim : %s", P->tim.namaTim);
            printf("\nPelatih : %s", P->tim.namaPelatih);
            if (haveChild(P))
            {
                C = P->firstChild;
                printChild(C);
            }
            else
                printf("\n \t BELUM ADA PEMAIN");
            P = P->nextParent;
        }
    }
}

void cariPemainBerdasarPosisi(ListParent L, string posisi) //modifikasi dari printChild + printAll
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
                        if (strcmpi(C->pemain.posisi, posisi) == 0)
                        {
                            printf("\n----------");
                            printf("\nNama pemain: %s", C->pemain.nama);
                            printf("\nPosisi : %s", C->pemain.posisi);
                            printf("\nTim: %s", P->tim.namaTim);
                        }
                        C = C->nextChild;
                    }
                }
            }
            P = P->nextParent;
        }
    }
}

void balaBantuan(ListParent *L, string timPenjual, string timPembeli)
{
    adrParent penerima = findParentByNamaTim((*L), timPembeli);
    adrParent pemberi = findParentByNamaTim((*L), timPenjual);

    if (pemberi != NULL && penerima != NULL)
    {
        if (haveChild(pemberi))
        {
            adrChild pemberiFirstChild = pemberi->firstChild;     //mengambil firstChild dari si Pemberi
            pemberi->firstChild = pemberi->firstChild->nextChild; //memindahkan firstChild Pemberi ke child berikutnya (firstChildnya menjadi si anak kedua)

            pemberiFirstChild->nextChild = penerima->firstChild; //firstChild yang diberikan, saudaranya menjadi firstChild si Penerima
            penerima->firstChild = pemberiFirstChild;            //firstChild penerima menjadi firstChild yang diberikan

            printf("\n\nBERHASIL PINDAH");
        }
        else
        {
            printf("\n\nPENJUAL TIDAK PUNYA PEMAIN");
        }
    }
    else
    {
        printf("\n\nSALAH SATU TIM TIDAK ADA");
    }
}