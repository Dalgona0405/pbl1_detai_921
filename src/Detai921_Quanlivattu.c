#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1
#define MIN_OPTION 1
#define MAX_OPTION 10

typedef struct {
	int ngay;
	int thang;
	int nam;
} date;

typedef struct {
	char Ma_VT[10];
	char Ten_VT[25];
	char Loai_VT[25];
	char Donvi[10];
	date ngaynhap;
	char Nha_sx[20];
	int So_luong;
	float Don_gia;
	float Thanh_tien;
} VatTu;

struct Node {
	struct Node *next;
	struct Node *prev;
	VatTu vt;
};
typedef struct Node Node;

typedef struct Node *List;
typedef struct Node *Position;

List create();
List tao_node(VatTu vt);
VatTu nhap_vattu(List L);
Position tim_node_cuoi(List L);
Position tim_node_k(List L, int k);
Position tim_vi_tri_chen_ma(List L, VatTu vt);
int them_VT(List L, VatTu vt, Position p);
void FindByMaVT(List L, char *Ma_VT);
void FindByTenVT(List L, char *Ten_VT);
void FindByLoai_VT(List L, char *Loai_VT);
void FindByNha_sx(List L, char *Nha_sx);
void timkiem(List L);
void sapxep_tenT(List L);
void sapxep_tenG(List L);
int sosanh_ngay(date a, date b);
void sapxep_ngayT(List L);
void sapxep_ngayG(List L);
void sapxep_soluongT(List L);
void sapxep_soluongG(List L);
void sapxep_dongiaT(List L);
void sapxep_dongiaG(List L);
void sapxep_thanhtienT(List L);
void sapxep_thanhtienG(List L);
void sapxep(List L);
int ktratrungMaVT(List L, char *Ma_VT);
int ktratrungTenVT(List L, char *Ten_VT);
void sua_sl_vattu(List L);
void xoavattu_lonhon100(List L);
void thongKeTheoLoai(List L);
float thanhtien(VatTu *vt);
int option(List L);
void docfile(List L, const char *filename);
void ghi_file(List L, const char *filename);
void show(List L);
void show_thanhtien(List L);

List create() {
	Position headerNode=malloc(sizeof(struct Node));
	if(headerNode==NULL)
		return NULL;
	headerNode->next=NULL;
	headerNode->prev=NULL;
	return headerNode;
}

List tao_node(VatTu vt) {
	List newNode=malloc(sizeof(struct Node));
	vt.Thanh_tien=thanhtien(&vt);
	newNode->vt=vt;
	newNode->next=NULL;
	newNode->prev=NULL;
	return newNode;
}

int them_VT(List L, VatTu vt, Position p) {
	if(p==NULL)
		p=L;
	Position newNode = tao_node(vt);
	if(newNode==NULL)
		return FALSE;
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

int ktratrungMaVT(List L, char *Ma_VT) {
	Node *p = L;
	while (p != NULL) {
		if (strcmp(p->vt.Ma_VT, Ma_VT) == 0) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

int ktratrungTenVT(List L, char *Ten_VT) {
	Node *p = L;
	while (p != NULL) {
		if (strcmp(p->vt.Ten_VT, Ten_VT) == 0) {
			return 1;
		}
		p = p->next;
	}
	return 0;
}

VatTu nhap_vattu(List L) {
	VatTu vt;

	do {
		printf("Ma vat tu: ");
		scanf(" %[^\n]", vt.Ma_VT);
		if (ktratrungMaVT(L, vt.Ma_VT)) {
			printf("Loi: Ma vat tu '%s' da ton tai! Vui long nhap lai.\n", vt.Ma_VT);
		} else {
			break;
		}
	} while (1);

	do {
		printf("Ten vat tu: ");
		scanf(" %[^\n]", vt.Ten_VT);
		if (ktratrungTenVT(L, vt.Ten_VT)) {
			printf("Loi: Ten vat tu '%s' da ton tai! Vui long nhap lai.\n", vt.Ten_VT);
		} else {
			break;
		}
	} while (1);

	printf("Loai vat tu: ");
	scanf(" %[^\n]", vt.Loai_VT);
	printf("Don vi tinh: ");
	scanf(" %[^\n]", vt.Donvi);
	printf("Ngay nhap (dd mm yyyy): ");
	scanf("%d%d%d", &vt.ngaynhap.ngay, &vt.ngaynhap.thang, &vt.ngaynhap.nam);
	printf("Nha san xuat: ");
	scanf(" %[^\n]", vt.Nha_sx);
	printf("So luong: ");
	scanf("%d", &vt.So_luong);
	printf("Don gia: ");
	scanf("%f", &vt.Don_gia);
	thanhtien(&vt);
	return vt;
}

void sua_sl_vattu(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong co vat tu de cap nhat.\n");
		return;
	}
	char ma[10];
	printf("Nhap ma vat tu can sua: ");
	scanf(" %[^\n]", ma);

	Position p = L->next;
	while (p != NULL) {
		if (strcmp(p->vt.Ma_VT, ma) == 0) {
			printf("Tim thay vat tu.\n");
			printf("So luong moi: ");
			scanf("%d", &p->vt.So_luong);
			printf("Don gia moi: ");
			scanf("%f", &p->vt.Don_gia);

			p->vt.Thanh_tien = thanhtien(&p->vt);
			ghi_file(L, "Vat_tu_moi.txt");
			printf("\nDa cap nhat vat tu thanh cong!\n");
			return;
		}
		p = p->next;
	}
	printf("\nKhong tim thay vat tu voi ma '%s'!\n", ma);
}

float thanhtien(VatTu *vt) {
	float giam_gia=0;
	if(vt->So_luong>200) {
		giam_gia=0.25;
	} else if(vt->So_luong > 100) {
		giam_gia=0.1;
	} else
		giam_gia=0;
	vt->Thanh_tien=vt->So_luong*vt->Don_gia*(1-giam_gia);
	return vt->Thanh_tien;
}

void thongKeTheoLoai(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong co du lieu thong ke.\n");
		return;
	}
	typedef struct {
		char loai[25];
		int tongSoLuong;
		float tongThanhTien;
	} ThongKe;

	ThongKe dsTK[100];
	int soLoai = 0;

	Position p = L->next;
	while (p != NULL) {
		int found = 0;
		for (int i = 0; i < soLoai; i++) {
			if (strcmp(dsTK[i].loai, p->vt.Loai_VT) == 0) {
				dsTK[i].tongSoLuong += p->vt.So_luong;
				dsTK[i].tongThanhTien += p->vt.Thanh_tien;
				found = 1;
				break;
			}
		}
		if (!found) {
			strcpy(dsTK[soLoai].loai, p->vt.Loai_VT);
			dsTK[soLoai].tongSoLuong = p->vt.So_luong;
			dsTK[soLoai].tongThanhTien = p->vt.Thanh_tien;
			soLoai++;
		}
		p = p->next;
	}

	printf("\n_________________THONG KE THEO LOAI VAT TU_________________________\n");
	printf("| %-25s | %-15s | %-17s |\n", "LOAI VAT TU", "TONG SO LUONG", "TONG THANH TIEN");
	printf("-------------------------------------------------------------------\n");

	for (int i = 0; i < soLoai; i++) {
		printf("| %-25s | %15d | %17.0f |\n", dsTK[i].loai, dsTK[i].tongSoLuong, dsTK[i].tongThanhTien);
	}

	printf("-------------------------------------------------------------------\n");
}

void FindByMaVT(List L, char *Ma_VT) {
	int found = 0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP",
	       "NHA SX", "SL", "DON GIA", "THANH TIEN");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL) {
		if(strcmp(L->vt.Ma_VT,Ma_VT)==0) {
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

void FindByTenVT(List L, char *Ten_VT) {
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP",
	       "NHA SX", "SL", "DON GIA", "THANH TIEN");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL) {
		if(strcmp(L->vt.Ten_VT,Ten_VT)==0) {
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

void FindByLoai_VT(List L, char *Loai_VT) {
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP",
	       "NHA SX", "SL", "DON GIA", "THANH TIEN");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL) {
		if(strcmp(L->vt.Loai_VT,Loai_VT)==0) {
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

void FindByNha_sx(List L, char *Nha_sx) {
	int found=0;
	L=L->next;
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP",
	       "NHA SX", "SL", "DON GIA", "THANH TIEN");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
	while(L!=NULL) {
		if(strcmp(L->vt.Nha_sx,Nha_sx)==0) {
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

Position tim_node_k(List L, int k) {
	Position p = L;
	int i=0;
	while(p!=NULL && i<k) {
		p=p->next;
		i++;
	}
	return p;
}

Position tim_vi_tri_chen_ma(List L, VatTu vt) {
	Position p = L;
	while (p->next != NULL && strcmp(p->next->vt.Ma_VT, vt.Ma_VT) < 0) {
		p = p->next;
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

void ghi_file(List L, const char *filename) {
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		printf("Khong the mo file de ghi!\n");
		return;
	}

	Position p = L->next;
	while (p != NULL) {
		fprintf(f, "%s;%s;%s;%s;%02d/%02d/%04d;%s;%d;%.0f;%.0f\n",
		        p->vt.Ma_VT, p->vt.Ten_VT, p->vt.Loai_VT, p->vt.Donvi,
		        p->vt.ngaynhap.ngay, p->vt.ngaynhap.thang, p->vt.ngaynhap.nam,
		        p->vt.Nha_sx, p->vt.So_luong, p->vt.Don_gia, p->vt.Thanh_tien);
		p = p->next;
	}

	fclose(f);
}

void show(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong co du lieu thong ke.\n");
		return;
	}
	printf("\n__________________________________________________________DANH SACH VAT TU______________________________________________________\n");
	printf("|%-10s|%-20s|%-20s|%-10s|%-11s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "LOAI VT", "DON VI", "NGAY NHAP",
	       "NHA SX", "SL", "DON GIA", "THANH TIEN");
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");

	L = L->next;
	while(L != NULL) {
		printf("|%-10s|%-20s|%-20s|%-10s|%02d/%02d/%04d |%-20s|%5d|%10.0f|%12.0f|\n",
		       L->vt.Ma_VT, L->vt.Ten_VT, L->vt.Loai_VT, L->vt.Donvi,
		       L->vt.ngaynhap.ngay, L->vt.ngaynhap.thang, L->vt.ngaynhap.nam,
		       L->vt.Nha_sx, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
		L = L->next;
	}
	printf("--------------------------------------------------------------------------------------------------------------------------------\n");
}

void show_thanhtien(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong co du lieu thong ke.\n");
		return;
	}
	printf("\n\t\t___________________DANH SACH THANH TIEN________________________\n");
	printf("\t\t|%-10s|%-20s|%-5s|%-10s|%-12s|\n",
	       "MA VT", "TEN VT", "SL", "DON GIA", "THANH TIEN");
	printf("\t\t---------------------------------------------------------------\n");

	L = L->next;
	while(L != NULL) {
		printf("\t\t|%-10s|%-20s|%5d|%10.0f|%12.0f|\n",
		       L->vt.Ma_VT, L->vt.Ten_VT, L->vt.So_luong, L->vt.Don_gia, L->vt.Thanh_tien);
		L = L->next;
	}
	printf("\t\t----------------------------------------------------------------\n");
}

void xoavattu_lonhon100(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong co vat tu de xoa.\n");
		return;
	}
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
		} else {
			p = p->next;
		}
	}
}

void sapxep_maT(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(strcmp(p->vt.Ma_VT, q->vt.Ma_VT) > 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep ma vat tu theo chieu tang dan.\n");
}

void sapxep_maG(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(strcmp(p->vt.Ma_VT, q->vt.Ma_VT) < 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep ten vat tu theo chieu giam dan.\n");
}

void sapxep_tenT(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(strcmp(p->vt.Ten_VT, q->vt.Ten_VT) > 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep ma vat tu theo chieu tang dan.\n");
}

void sapxep_tenG(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(strcmp(p->vt.Ten_VT, q->vt.Ten_VT) < 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep ten vat tu theo chieu giam dan.\n");
}

int sosanh_ngay(date a, date b) {
	if (a.nam != b.nam)
		return a.nam - b.nam;
	if (a.thang != b.thang)
		return a.thang - b.thang;
	return a.ngay - b.ngay;
}

void sapxep_ngayT(List L) {
	for (Position p = L->next; p != NULL; p = p->next) {
		for (Position q = p->next; q != NULL; q = q->next) {
			if (sosanh_ngay(p->vt.ngaynhap, q->vt.ngaynhap) > 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep danh sach theo ngay nhap tang dan.\n");
}

void sapxep_ngayG(List L) {
	for (Position p = L->next; p != NULL; p = p->next) {
		for (Position q = p->next; q != NULL; q = q->next) {
			if (sosanh_ngay(p->vt.ngaynhap, q->vt.ngaynhap) < 0) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep danh sach theo ngay nhap giam dan.\n");
}

void sapxep_soluongT(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.So_luong > q->vt.So_luong) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep so luong theo chieu tang dan.\n");
}

void sapxep_soluongG(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.So_luong < q->vt.So_luong) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep so luong theo chieu giam dan.\n");
}

void sapxep_dongiaT(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.Don_gia > q->vt.Don_gia) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep don gia theo chieu tang dan.\n");
}

void sapxep_dongiaG(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.Don_gia < q->vt.Don_gia) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep don gia theo chieu giam dan.\n");
}

void sapxep_thanhtienT(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.Thanh_tien > q->vt.Thanh_tien) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep thanh tien theo chieu tang dan.\n");
}

void sapxep_thanhtienG(List L) {
	for(Position p = L->next; p != NULL; p = p->next) {
		for(Position q = p->next; q != NULL; q = q->next) {
			if(p->vt.Thanh_tien < q->vt.Thanh_tien) {
				VatTu temp = p->vt;
				p->vt = q->vt;
				q->vt = temp;
			}
		}
	}
	printf("Da sap xep thanh tien theo chieu giam dan.\n");
}

void sapxep(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong the sap xep.\n");
		return;
	}
	int c;
	char x;
	printf("1. Sap xep theo ma vat tu.\n");
	printf("2. Sap xep theo ten.\n");
	printf("3. Sap xep theo ngay nhap.\n");
	printf("4. Sap xep theo so luong.\n");
	printf("5. Sap xep theo don gia.\n");
	printf("6. Sap xep theo thanh tien.\n");
	printf("Ban muon sap xep theo tieu chi nao? Tieu chi: ");
	scanf("%d",&c);
	getchar();

	switch(c) {
		case 1:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_maT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_maG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		case 2:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_tenT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_tenG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		case 3:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_ngayT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_ngayG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		case 4:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_soluongT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_soluongG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		case 5:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_dongiaT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_dongiaG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		case 6:
			printf("Ban muon sap xep theo chieu tang dan hay giam dan? [T/G]: ");
			scanf(" %c", &x);
			if(x=='T'||x=='t') {
				sapxep_thanhtienT(L);
				show(L);
			} else if (x=='G'||x=='g') {
				sapxep_thanhtienG(L);
				show(L);
			} else printf("Lua chon khong hop le.\n");
			break;
		default:
			printf("Lua chon khong hop le.\n");
	}
}

void timkiem(List L) {
	if (L->next == NULL) {
		printf("Danh sach rong, khong the tim kiem.\n");
		return;
	}
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

void menu() {
	printf("\t\t -----------QUAN LY VAT TU----------------- \n");
	printf("\t\t| 1. In danh sach vat tu                   |\n");
	printf("\t\t| 2. Them vat tu vao danh sach             |\n");
	printf("\t\t| 3. Tim kiem vat tu                       |\n");
	printf("\t\t| 4. Sap xep vat tu theo yeu cau           |\n");
	printf("\t\t| 5. Chen vat tu vao vi tri bat ki         |\n");
	printf("\t\t| 6. Chen vat tu vao danh sach da sap xep  |\n");
	printf("\t\t| 7. Xoa vat tu co so luong hon 100        |\n");
	printf("\t\t| 8. Cap nhat so luong va don gia          |\n");
	printf("\t\t| 9. Bang thong ke theo loai vat tu        |\n");
	printf("\t\t| 10. Dung chuong trinh                    |\n");
	printf("\t\t ------------------------------------------ \n");
}

int option(List L) {
	int opt;
	char newline;
	char x;
	menu();
	printf("\nNhap chuc nang muon su dung (1 - 10): ");
	if (scanf("%d%c", &opt, &newline) != 2 || newline != '\n') {
		printf("? Nhap khong hop le. Vui long nhap so nguyen trong khoang 1 den 10.\n");
		while (getchar() != '\n');
		return 0;
	}
	if (opt < 1 || opt > 10) {
		printf("? Lua chon khong nam trong menu. Vui long chon tu 1 den 10.\n");
		return 0;
	}
	switch(opt) {
		case 1:
			show(L);
			break;
		case 2: {
			VatTu vt = nhap_vattu(L);
			Position p = tim_node_cuoi(L);
			them_VT(L, vt, p);
			ghi_file(L, "Vat_tu_moi.txt");
			printf("Da them vat tu va cap nhat file.\n");
			break;
		}
		case 3:
			timkiem(L);
			break;
		case 4:
			sapxep(L);
			break;
		case 5: {
			char x;
			int k;
			printf("Nhap vi tri ma ban muon chen vao (1, 2, 3, ....): ");
			scanf("%d",&k);
			VatTu vt = nhap_vattu(L);
			Position p=tim_node_k(L, k-1);
			them_VT(L,vt,p);
			ghi_file(L, "Vat_tu_moi.txt");
			printf("Ban co muon xem danh sach sau khi da chen khong? [Y/N] ");
			scanf(" %c",&x);
			if(x=='Y'||x=='y') {
				printf("Danh sach sau khi da chen: \n");
				show(L);
			}
			break;
		}
		case 6: {
			VatTu vt = nhap_vattu(L);
			sapxep_maT(L);
			Position vitri = tim_vi_tri_chen_ma(L, vt);
			them_VT(L, vt, vitri);
			ghi_file(L, "Vat_tu_moi.txt");
			printf("Da chen vao dung vi tri theo thu tu tang dan Ma_VT.\n");
			show(L);
			break;
		}
		case 7:
			xoavattu_lonhon100(L);
			printf("Danh sach vat tu sau khi xoa: \n");
			show(L);
			ghi_file(L, "Vat_tu_moi.txt");
			break;
		case 8: {
			char c;
			sua_sl_vattu(L);
			ghi_file(L, "Vat_tu_moi.txt");
			printf("Ban co muon xem lai danh sach thanh tien sau khi cap nhat khong? [Y/N] ");
			scanf(" %c",&c);
			if(c=='Y'||c=='y')
				show_thanhtien(L);
			break;
		}
		case 9:
			thongKeTheoLoai(L);
			break;
		case 10:
			printf("Ket thuc chuong trinh.\n");
			return 1;
		default:
			printf("\n  Lua chon khong hop le! \n");
	}
	return 0;
}

void freeList(List L) {
	Position p = L;
	while (p != NULL) {
		Position temp = p;
		p = p->next;
		free(temp);
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
	int tieptuc = 1;
	while(tieptuc) {
		printf("--------------------------------------------------------------------------------------------------------------------------------\n");
		int daDung = option(ds_vattu);
		if (daDung == 1) break;
		printf("Ban co muon tiep tuc chuong trinh khong? [Y/N]: ");
		scanf(" %c",&x);
		if (x!='Y' && x!='y')
			break;
	}
	freeList(ds_vattu);
	return 0;
}