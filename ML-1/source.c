#include "header.h"

void showMenu()
{
    printf("\n1. Daftarkan cabang baru");
    printf("\n2. Cari caban di suatu negara");
    printf("\n3. Daftarkan anggota baru");
    printf("\n4. Pangkas anggota");
    printf("\n5. Tampilkan cabang dan anggota seluruh dunia");
    printf("\n\n BONUS");
    printf("\n6. Bubarkan cabang");
    printf("\n7. lacak agen");
    printf("\n\n TUGAS");
    printf("\n8. Bala bantuan");
}

Cabang makeCabang(string kodeCabang, string namaNegara)
{
    Cabang cabang;
    strcpy(cabang.kodeCabang, kodeCabang);
    strcpy(cabang.negara, namaNegara);

    return cabang;
}

adrParent alokasiCabang(Cabang cabang)
{
    adrParent P;
    P = (adrParent)malloc(sizeof(Parent));
    P->cabang = cabang;
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

void insertFirstParent(ListParent *L, Cabang databaru)
{
    adrParent P;
    P = alokasiCabang(databaru);
    P->nextParent = (*L).first;
    (*L).first = P;
    printf("\n\nBERHASIL INSERT CABANG [first insert]");
}

void insertLastParent(ListParent *L, Cabang databaru)
{
    adrParent P, last;
    if (isEmpty(*L))
        insertFirstParent(&(*L), databaru);
    else
    {
        P = alokasiCabang(databaru);
        last = (*L).first;
        while (last->nextParent != NULL)
        {
            last = last->nextParent;
        }
        last->nextParent = P;
        printf("\n\nBERHASIL INSERT CABANG [last insert]");
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
        printf("\nDELETED CABANG PERTAMA");
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
            printf("DELETED LAST CABANG");
        }
    }
}
void deleteAfterParent(ListParent *L, string kodeCabang)
{
    adrParent del, cari;
    cari = findParentByKodeCabang((*L), kodeCabang);
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

adrParent findParentByKodeCabang(ListParent L, string kodeCabang) //modified from findParent
{
    adrParent P = L.first;
    while (P != NULL)
    {
        if (strcmpi(P->cabang.kodeCabang, kodeCabang) != 0)
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

void printCabangByNegara(ListParent L, string namaNegara)
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
            if (strcmpi(P->cabang.negara, namaNegara) == 0)
            {
                printf("\n\nKode cabang : %s", P->cabang.kodeCabang);
                printf("\nNegara : %s", P->cabang.negara);
            }
            P = P->nextParent;
        }
    }
}

Anggota makeAnggota(string id, string nama)
{
    Anggota anggota;
    strcpy(anggota.id, id);
    strcpy(anggota.nama, nama);

    return anggota;
}

adrChild AlokasiC(Anggota anggotaBaru)
{
    adrChild C;
    C = (adrChild)malloc(sizeof(Child));
    C->anggota = anggotaBaru;
    C->nextChild = NULL;
    return C;
}

void insertFirstChildToParentCabang(ListParent *L, string kodeCabang, Anggota anggotaBaru)
{
    adrChild C;
    adrParent P;
    P = findParentByKodeCabang((*L), kodeCabang);
    if (P == NULL)
        printf("Cabang tidak ada");
    else
    {
        C = AlokasiC(anggotaBaru);
        C->nextChild = P->firstChild;
        P->firstChild = C;
        printf("\nBERHASIL INSERT ANGGOTA %s KE CABANG %s", anggotaBaru.nama, kodeCabang);
    }
}

void deleteFirstChild(ListParent *L, string kodeCabangParent)
{
    adrChild del;
    adrParent P;
    P = findParentByKodeCabang((*L), kodeCabangParent);
    if (P == NULL)
        printf("Cabang tidak ada");
    else if (!haveChild(P))
        printf("\nTidak ada anggota di cabang ini");
    else
    {
        del = P->firstChild;
        P->firstChild = P->firstChild->nextChild;
        free(del);
        printf("DELETED ANGGOTA FROM %s", kodeCabangParent);
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
            printf("\n \t -  %s, %s", C->anggota.id, C->anggota.nama);
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
            printf("\n\nKode cabang : %s", P->cabang.kodeCabang);
            printf("\nNegara : %s", P->cabang.negara);
            if (haveChild(P))
            {
                C = P->firstChild;
                printChild(C);
            }
            else
                printf("\n \t BELUM ADA ANGGOTA");
            P = P->nextParent;
        }
    }
}

void lacakAgent(ListParent L, string id)
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
                        if (strcmpi(C->anggota.id, id) == 0)
                        {
                            printf("\n----------");
                            printf("\nid agen: %s", C->anggota.id);
                            printf("\nnama agen : %s", C->anggota.nama);
                            printf("\nnegara: %s", P->cabang.negara);
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
void balaBantuan(ListParent *L, string pemberiBantuan, string penerimaBantuan)
{
    adrParent penerima = findParentByKodeCabang((*L), penerimaBantuan);
    adrParent pemberi = findParentByKodeCabang((*L), pemberiBantuan);

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
            printf("\n\nPEMBERI TIDAK PUNYA ANGGOTA");
        }
    }
    else
    {
        printf("\n\nSALAH SATU CABANG TIDAK ADA");
    }
}