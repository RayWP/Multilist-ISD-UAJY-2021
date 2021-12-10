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
	string kodeCabang;
	string negara;
} Cabang;

typedef struct
{
	string id;
	string nama;
} Anggota;

typedef struct tParent
{
	Cabang cabang;
	adrParent nextParent;
	adrChild firstChild;
} Parent;

typedef struct tChild
{
	Anggota anggota;
	adrChild nextChild;
} Child;

typedef struct
{
	adrParent first;
} ListParent;

void showMenu();
int isEmpty(ListParent L);
void createEmpty(ListParent *L);

Cabang makeCabang(string kodeCabang, string namaNegara);
adrParent alokasiCabang(Cabang cabang);
int haveChild(adrParent P);
void insertFirstParent(ListParent *L, Cabang databaru);
void insertLastParent(ListParent *L, Cabang databaru);
void deleteFirstParent(ListParent *L);
adrParent findParentByKodeCabang(ListParent L, string kodeCabang);
void printCabangByNegara(ListParent L, string namaNegara);

Anggota makeAnggota(string id, string nama);
adrChild AlokasiC(Anggota anggotaBaru);
void insertFirstChildToParentCabang(ListParent *L, string kodeCabang, Anggota anggotaBaru);
void deleteFirstChild(ListParent *L, string kodeCabangParent);
void printChild(adrChild C);
void printAll(ListParent L);
void lacakAgent(ListParent L, string id);
void balaBantuan(ListParent *L, string pemberiBantuan, string penerimaBantuan);