#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

#define FALSE 0
#define TRUE 1

typedef struct{
	int ngay;
	int thang;
	int nam;
} date;

typedef struct{
	char Ma_VT[10];
	char Ten_VT[20];
	char Loai_VT[10];
	char Donvi[10];
	date ngaynhap;
	char Nha_sx[20];
	int So_luong;
	float Don_gia;
	float Thanh_tien;
} VatTu;

struct Node{
	struct Node *next;
	struct Node *prev;
	VatTu vt;
};

typedef struct Node *List;
typedef struct Node *Position;

List create();
List tao_node(VatTu vt);
VatTu nhap_vattu();
Position tim_node_cuoi(List L);
Position tim_node_k(List L, int k);
int them_VT(List L, VatTu vt, Position p);
void FindByMaVT(List L, char *Ma_VT);
void FindByTenVT(List L, char *Ten_VT);
void FindByLoai_VT(List L, char *Loai_VT);
void FindByNha_sx(List L, char *Nha_sx);
void xoavattu_lonhon100(List L);
float thanhtien(VatTu *vt);
void docfile(List L, const char *filename);
void show(List L);

List create(){
	Position headerNode=malloc(sizeof(struct Node));
	if(headerNode==NULL)
		return NULL;
	headerNode->next=NULL;
	headerNode->prev=NULL;
	return headerNode;
}

List tao_node(VatTu vt){
	List newNode=malloc(sizeof(struct Node));
	vt.Thanh_tien=thanhtien(&vt);
	newNode->vt=vt;
	newNode->next=NULL;
	newNode->prev=NULL;
	return newNode;
}

VatTu nhap_vattu() {
    VatTu vt;

    printf("Nhap ma vat tu: ");        			scanf(" %[^\n]", vt.Ma_VT);
    printf("Nhap ten vat tu: ");       			scanf(" %[^\n]", vt.Ten_VT);
    printf("Nhap loai vat tu: ");      			scanf(" %[^\n]", vt.Loai_VT);
    printf("Nhap don vi tinh: ");      			scanf(" %[^\n]", vt.Donvi);
    printf("Nhap ngay nhap (dd mm yyyy): ");	scanf("%d%d%d", &vt.ngaynhap.ngay, &vt.ngaynhap.thang, &vt.ngaynhap.nam);
    printf("Nhap nha san xuat: ");     			scanf(" %[^\n]", vt.Nha_sx);
    printf("Nhap so luong: ");         			scanf("%d", &vt.So_luong);
    printf("Nhap don gia: ");          			scanf("%f", &vt.Don_gia);
    thanhtien(&vt);
    return vt;
}


int them_VT(List L, VatTu vt, Position p){
	if(p==NULL)
		p=L;
	Position newNode=malloc(sizeof(struct Node));
	if(newNode==NULL)
		return FALSE;
	newNode->vt=vt;
	newNode->next=p->next;
	newNode->prev=p;
	p->next=newNode;
	if(newNode->next!=NULL)
		newNode->next->prev=newNode;
		return TRUE;
}

Position tim_node_cuoi(List L) {
    Position p = L;
    while (p->next != NULL)
        p = p->next;
    return p;
}

float thanhtien(VatTu *vt){
	float giam_gia=0;
	if(vt->So_luong>200){
		giam_gia=0.25;
	}
	else if(vt->So_luong > 100 && vt->So_luong <= 200){
		giam_gia=0.1;
	}
	else if(vt->So_luong<=100){
		giam_gia=0;
	}
	vt->Thanh_tien=vt->So_luong*vt->Don_gia*(1-giam_gia);
	return vt->Thanh_tien;
}

void FindByMaVT(List L, char *Ma_VT){
	int found = 0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
           "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP", 
           "NHA SX", "SL", "DON GIA", "THANH TIEN");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL){
		if(strcmp(L->vt.Ma_VT,Ma_VT)==0){
			printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
               L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
               L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
               L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            found++;
		}
		L = L->next;
	}
	if(!found)
	printf("Khong tim duoc.\n");

}

void FindByTenVT(List L, char *Ten_VT){
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
           "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP", 
           "NHA SX", "SL", "DON GIA", "THANH TIEN");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL){
		if(strcmp(L->vt.Ten_VT,Ten_VT)==0){
			printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
               L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
               L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
               L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
        	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
        	found++;
		}
		L = L->next;
	}
	if(!found)
		printf("Khong tim duoc.\n");
}

void FindByLoai_VT(List L, char *Loai_VT){
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
           "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP", 
           "NHA SX", "SL", "DON GIA", "THANH TIEN");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL){
		if(strcmp(L->vt.Loai_VT,Loai_VT)==0){
			printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
               L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
               L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
               L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien); 
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            found++;
		}
		L = L->next;
	}
	if(!found)
		printf("Khong tim duoc.\n");
}

void FindByNha_sx(List L, char *Nha_sx){
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
           "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP", 
           "NHA SX", "SL", "DON GIA", "THANH TIEN");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL){
		if(strcmp(L->vt.Nha_sx,Nha_sx)==0){
			printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
               L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
               L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
               L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
            printf("--------------------------------------------------------------------------------------------------------------------------------\n");
            found++;
		}
		L = L->next;
	}
	if(!found)
		printf("Khong tim duoc.\n");
}

Position tim_node_k(List L, int k){
	Position p = L;
	int i=0;
	while(p!=NULL && i<k){
		p=p->next;
		i++;
	}
	return p;
}

void docfile(List L, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Khong the mo file %s\n", filename);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), f)) {
        VatTu vt;
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%[^;];%[^;];%[^;];%[^;];%d/%d/%d;%[^;];%d;%f",
               vt.Ma_VT, vt.Ten_VT, vt.Loai_VT, vt.Donvi,
               &vt.ngaynhap.ngay, &vt.ngaynhap.thang, &vt.ngaynhap.nam,
               vt.Nha_sx, &vt.So_luong, &vt.Don_gia);

        thanhtien(&vt);
        them_VT(L, vt, tim_node_cuoi(L));
    }

    fclose(f);
}

void show(List L){
    printf("\n__________________________________________________________DANH SACH VAT TU______________________________________________________\n");
    printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
           "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP", 
           "NHA SX", "SL", "DON GIA", "THANH TIEN");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    
    L = L->next;
    while(L != NULL){
        printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
               L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
               L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
               L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
        L = L->next; 
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void xoavattu_lonhon100(List L) {
	Position p = L->next;
	while (p != NULL) {
		if (p->vt.So_luong > 100) {
			printf("Xoa vat tu: %s - So luong: %d\n", p->vt.Ma_VT, p->vt.So_luong);
			Position temp = p;
			p->prev->next = p->next;
			if (p->next != NULL)
				p->next->prev = p->prev;
			p = p->next;
			free(temp);
		}
		else {
			p = p->next;
		}
	}
}

void intro() {
	printf(" \t ________________________________________________________\n");
	printf("\t|         Truong       : DHBK Da Nang                    |\n");
	printf("\t|         Khoa         : Cong nghe thong tin             |\n");
	printf("\t|         PBL1         : Do an lap trinh tinh toan       |\n");
	printf("\t|         De tai       : Quan li vat tu                  |\n");
	printf("\t|         GV huong dan : Do Thi Tuyet Hoa                |\n");
	printf("\t|         Sinh vien    : Bui An Binh                     |\n");
	printf("\t|                        Thi Nguyen Thanh Truc           |\n");
	printf("\t|________________________________________________________|\n");
}

void menu(){
	printf("\t\t -----------QUAN LY VAT TU---------- \n");
	printf("\t\t| 1. In danh sach vat tu            |\n");
	printf("\t\t| 2. Them vat tu vao danh sach      |\n");
	printf("\t\t| 3. Tim kiem vat tu                |\n");
	printf("\t\t| 4. Sap xep vat tu theo yeu cau    |\n");
	printf("\t\t| 5. Chen vat tu vao vi tri bat ki  |\n");
	printf("\t\t| 6. Chen vat tu va sap xep         |\n");
	printf("\t\t| 7. Xoa vat tu co so luong hon 100 |\n");
	printf("\t\t| 8. Thanh tien                     |\n");
	printf("\t\t| 9. Bang thong ke theo loai vat tu |\n");
	printf("\t\t| 10. Dung chuong trinh             |\n");
	printf("\t\t ----------------------------------- \n");
}

void option(List L){
	int opt;
	VatTu vt;
	char x;
		menu();
		printf("\nNhap chuc nang muon su dung: ");
		scanf("%d",&opt);
		switch(opt){
			case 1:
				show(L);
				break;
			case 2:{
				VatTu vt=nhap_vattu();
				printf("Ban muon them vao dau hay cuoi [D/C]: ");
				scanf(" %c",&x);
				if(x=='D'||x=='d'){
					them_VT(L, vt, NULL);
				} else if(x=='C'||x=='c'){
					Position p = tim_node_cuoi(L);
					them_VT(L, vt, p);
				} else {
					printf("Lua chon khong hop le. Vui long thu lai!\n");
					break;
				}
				printf("Da them thanh cong.\n");
				break;
			}
			case 3: {
    			int c;
    			char x[50];
    			printf("\n1. Tim kiem theo Ma_VT.\n");
    			printf("2. Tim kiem theo TenVT.\n");
    			printf("3. Tim kiem theo Loai_VT.\n");
    			printf("4. Tim kiem theo Nha_sx.\n");
    			printf("Ban muon tim kiem theo tieu chi nao? Tieu chi: ");
    			scanf("%d", &c);
    			getchar();

    			switch(c) {
       				case 1:
            			printf("Nhap MaVT can tim: ");
            			scanf(" %[^\n]", x);
            			FindByMaVT(L, x);
            			break;
        			case 2:
            			printf("Nhap TenVT can tim: ");
            			scanf(" %[^\n]", x);
            			FindByTenVT(L, x);
            			break;
        			case 3:
            			printf("Nhap Loai_VT can tim: ");
            			scanf(" %[^\n]", x);
            			FindByLoai_VT(L, x);
            			break;
        			case 4:
            			printf("Nhap Nha_sx can tim: ");
            			scanf(" %[^\n]", x);
            			FindByNha_sx(L, x);
            			break;
        			default:
            			printf("Lua chon khong hop le.\n");
    			}
    			break;
			}
			case 4:
				break;
			case 5:{
				char x;
				int k;
				printf("Nhap vi tri ma ban muon chen vao (1, 2, 3, ....): ");
				scanf("%d",&k);
				VatTu vt = nhap_vattu();
				Position p=tim_node_k(L, k-1);
				them_VT(L,vt,p);
				printf("Ban co muon xem danh sach sau khi da chen khong? [Y/N] ");
				scanf(" %c",&x);
				if(x=='Y'||x=='y'){
				printf("Danh sach sau khi da chen: \n");
				show(L);
				} else break;
				break;
			}
			case 6:
				break;
			case 7:
				xoavattu_lonhon100(L);
				printf("Danh sach vat tu sau khi xoa: \n");
				show(L);
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				printf("Ket thuc chuong trinh.\n");
				break;
			default:
				printf("\n  Lua chon khong hop le! \n");
		}
	}

int main() {
	char x;
	List ds_vattu = create();
	if (ds_vattu == NULL) {
		printf("Khong the cap phat bo nho cho danh sach!\n");
		return 1;
	}
	docfile(ds_vattu, "Vat_tu.txt");  
	intro();
	do{
		printf("--------------------------------------------------------------------------------------------------------------------------------\n");
		option(ds_vattu);
		printf("Ban co muon tiep tuc chuong trinh khong? [Y/N]: ");
		scanf(" %c",&x);
	} while (x=='Y'||x=='y');
		return 0;
}
