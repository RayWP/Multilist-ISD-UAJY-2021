#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <string.h>

typedef char string[100];
typedef struct tChild *adrChild;
typedef struct tParent *adrParent;

typedef struct
{
	string namaTim;
	string namaPelatih;
} Tim;

typedef struct
{
	string nama;
	string posisi;
} Pemain;

typedef struct tParent
{
	Tim tim;
	adrParent nextParent;
	adrChild firstChild;
} Parent;

typedef struct tChild
{
	Pemain pemain;
	adrChild nextChild;
} Child;

typedef struct
{
	adrParent first;
} ListParent;

void showMenu();
int isEmpty(ListParent L);
void createEmpty(ListParent *L);

Tim makeTim(string namaTim, string namaPelatih);
adrParent alokasiTim(Tim timBaru);
int haveChild(adrParent P);
void insertFirstParent(ListParent *L, Tim databaru);
void insertLastParent(ListParent *L, Tim databaru);
void deleteFirstParent(ListParent *L);
adrParent findParentByNamaTim(ListParent L, string namaTim);
void printTimByPelatih(ListParent L, string namaPelatih);

Pemain makePemain(string nama, string posisi);
adrChild AlokasiC(Pemain anggotaBaru);
void insertFirstChildToParentTim(ListParent *L, string namaTim, Pemain anggotaBaru);
void deleteFirstChild(ListParent *L, string namaTim);
void deleteLastChild(ListParent *L, string namaTim);
void printChild(adrChild C);
void printAll(ListParent L);
void cariPemainBerdasarPosisi(ListParent L, string nama);
void balaBantuan(ListParent *L, string timPenjual, string timPembeli);