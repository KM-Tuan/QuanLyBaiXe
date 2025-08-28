//Viết một chương trình quản lý bãi xe gồm có các chức năng: 
//+ Nhận 1 xe vào bãi => Khi nhận xe vào phải kiểm tra xem là xe được gởi theo tháng hay gởi theo ngày. ("1" theo tháng, "2" theo ngày)
//Lưu xe vừa vào bãi vào trong danh sách các xe đang đậu trong bãi 
//+ Xuất 1 xe ra bãi => nếu là xe gởi trong ngày, thì phải tính tiền bãi. 
//Nếu thời gian trong bãi dưới 60 phút thì tính 50.000 vnd. Với mỗi 30 phút tiếp theo, sẽ tính thêm 20.000 vnd + Thống kê số lượng xe đang có trong bãi và tiền bãi đã thu được.
// Sử dụng struct để giải quyết bài toán này

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>
#include <conio.h>
using namespace std;

struct Xe
{
    string bienSo;
    int loaiGui;
    char thoiGianNhan[7] = "";
};

struct BaiXe
{
    Xe **xe;
    Xe *xeThang;
    int maxXeNgay = 4;
    int tienThu = 0;
};

//Khoi tao
string random();
void init_BaiXe(BaiXe *&bx, int &n);
void init_xeThang(BaiXe *&bx, int &m);
void init_Xe(BaiXe *&bx, int &r, int &c);

//Nhan xe
bool isXeThang(BaiXe *bx, string id, int m);
void ghiThongTinXeThang(BaiXe *bx, int r, int c, string id);
bool isChoTrongXeNgay(BaiXe *bx, int m);
void ghiThongTinXeNgay(BaiXe *bx, int r, int c, string id);
void nhanXe(BaiXe *bx, int r, int c, string bienSoXe, int m);

//Tra xe
void khoiTaoTempXe(Xe **&temp_xe, int r, int c);
bool isTonTai(BaiXe *bx, int r, int c, string id);
void saoChepXe(BaiXe *bx, Xe **temp_xe, int r, int c, char *c_time, string id);
void tinhTienGuiXe(BaiXe *bx, char *c_time, string id);
void traXe(BaiXe *bx, int r, int c, string id, int m);

//Thong ke
void thongKe(BaiXe *bx, int r, int c);

//Xuat thong tin
void output_xeThang(BaiXe *bx, int m);
void output(BaiXe *bx, int r, int c);

//Giai phong du lieu
void delete_xe(BaiXe *bx, int r);
void delete_xeThang(BaiXe *bx);
void delete_baiXe(BaiXe *bx);

int main()
{
    srand(time(NULL));
    int choose, n, m, r, c;
    string bienSo;
    BaiXe *bx;

    init_BaiXe(bx, n);
    init_xeThang(bx, m);
    init_Xe(bx, r, c);

    do
    {
        system("cls");
        output_xeThang(bx, m);
        cout << "==== QUAN LY BAI XE ====" << endl
            << "1. NHAN XE: " << endl
            << "2. XEM BAI: " << endl
            << "3. TRA XE: " << endl
            << "4. THONG KE: " << endl
            << "0. EIXT: " << endl
            << "Chon: "; cin >> choose;
        switch (choose)
        {
            case 0:
                //Giai phong cac xe;
                delete_xe(bx, r);

                //Giai phong xe thang
                delete_xeThang(bx);

                //Giai phong bai xe
                delete_baiXe(bx);
                break;
            case 1:
                cout << "Nhap bien so xe: "; cin >> bienSo;
                nhanXe(bx, r, c, bienSo, m);
                break;
            case 2:
                output(bx, r, c);
                break;
            case 3:
                cout << "Nhap bien so xe: "; cin >> bienSo;
                traXe(bx, r, c, bienSo, m);
                break;
            case 4:
                cout << "============ THONG KE ============" << endl;
                thongKe(bx, r, c);
                break;
            default:
                cout << "Lua chon khong hop le!!" << endl;
        }
        _getch();
    } while (choose != 0);
    
}

//Khoi tao xe & bai xe
string random()
{
    //Khoi tao bien so xe gom 2 chu & 4 so
    string box_1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string box_2 = "0123456789";
    string arr = "";
    for (int i = 0; i < 2; i++)
        arr += box_1[rand() % 26];

    for (int i = 0; i < 4; i++)
        arr += box_2[rand() % 10];

    return arr;
}
void init_BaiXe(BaiXe *&bx, int &n)
{
    n = 2;
    bx = new BaiXe[n];
}
void init_xeThang(BaiXe *&bx, int &m)
{
    m = 6;

    bx->xeThang = new Xe[m];
    for (int i = 0; i < 6; i++)
        bx->xeThang[i].bienSo = random();
}
void init_Xe(BaiXe *&bx, int &r, int &c)
{
    r = 2; 
    c = 5;

    bx->xe = new Xe*[r];
    for (int i = 0; i < r; i++)
        bx->xe[i] = new Xe[c];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            bx->xe[i][j].bienSo = "NULL";
            bx->xe[i][j].loaiGui = 0;
            strcpy(bx->xe[i][j].thoiGianNhan, "NULL");
        }
    }
}

//Nhan xe
bool isXeThang(BaiXe *bx, string id, int m)
{
    for (int i = 0; i < m; i++)
        if (bx->xeThang[i].bienSo == id)
            return true;
    return false;
}
void ghiThongTinXeThang(BaiXe *bx, int r, int c, string id)
{
    cout << "Xe thuoc loai xe thang!" << endl;
    bx->xe[r][c].bienSo = id;
    bx->xe[r][c].loaiGui = 1;
    cout << "Nhan xe thanh cong!!" << endl;
}
bool isChoTrongXeNgay(BaiXe *bx, int m)
{
    if (bx->maxXeNgay == 0)
        return false;
    return true;
}
void ghiThongTinXeNgay(BaiXe *bx, int r, int c, string id)
{
    cout << "Xe thuoc loai xe ngay!" << endl;
    bx->xe[r][c].bienSo = id;
    bx->xe[r][c].loaiGui = 2;
    
    cin.ignore();
    char time[7] = "";
    cout << "Thoi gian nhan xe: "; 
    cin.getline(time, 7);
    strcpy(bx->xe[r][c].thoiGianNhan, time);
    bx->maxXeNgay--;
    cout << "Nhan xe thanh cong!!" << endl;
}
void nhanXe(BaiXe *bx, int r, int c, string bienSoXe, int m)
{
    bool checkNhanXe = false;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            //Kiem tra cho trong
            if (bx->xe[i][j].bienSo == "NULL")
            {
                //Kiem tra xe thang & ghi thong tin
                if (isXeThang(bx, bienSoXe, m))
                    ghiThongTinXeThang(bx, i, j, bienSoXe);
                //Kiem tra cho trong cho xe ngay & ghi thong tin
                else
                {
                    cout << "Cho hien tai danh cho xe ngay: " << bx->maxXeNgay << endl;
                    if (isChoTrongXeNgay(bx, m))
                        ghiThongTinXeNgay(bx, i, j, bienSoXe);
                    else
                        cout << "Da het cho danh cho xe ngay!!" << endl;
                }
                checkNhanXe = true;
                break;
            }
            //Kiem tra xe da duoc gui hay chua
            else if (bx->xe[i][j].bienSo == bienSoXe)
            {
                cout << "Xe dang duoc gui trong bai!!" << endl;
                checkNhanXe = true;
                break;
            }
            else if (i == r - 1 && j == c - 1)
                cout << "Bai xe da het cho!!" << endl;
        }
        if (checkNhanXe)
            break;
    }
}

//Tra xe
void khoiTaoTempXe(Xe **&temp_xe, int r, int c)
{
    temp_xe = new Xe*[r];
    for (int i = 0; i < r; i++)
        temp_xe[i] = new Xe[c];

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            temp_xe[i][j].bienSo = "NULL";
            temp_xe[i][j].loaiGui = 0;
            strcpy(temp_xe[i][j].thoiGianNhan, "NULL");
        }
    }    
}
bool isTonTai(BaiXe *bx, int r, int c, string id)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            if (bx->xe[i][j].bienSo == id)
                return true;
    }
    return false;
}
void saoChepXe(BaiXe *bx, Xe **temp_xe, int r, int c, char *c_time, string id)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (bx->xe[i][j].bienSo != id)
            {
                temp_xe[i][j].bienSo = bx->xe[i][j].bienSo;
                temp_xe[i][j].loaiGui = bx->xe[i][j].loaiGui;
                strcpy(temp_xe[i][j].thoiGianNhan, bx->xe[i][j].thoiGianNhan);
            }
            else
                strcpy(c_time, bx->xe[i][j].thoiGianNhan);
        }
    }

    for (int i = 0; i < r; i++)
        delete[] bx->xe[i];
    delete[] bx->xe;
    bx->xe = temp_xe;
    temp_xe = NULL;
}
void tinhTienGuiXe(BaiXe *bx, char *c_time, string id)
{
    int min, hour, c_min, c_hour;
    char *c_ptok = strtok(c_time, "h");
    c_hour = atoi(c_ptok);
    c_ptok = strtok(NULL, "h");
    c_min = atoi(c_ptok);

    cin.ignore();
    char time[7] = "";
    cout << "Nhap thoi gian tra xe: "; 
    cin.getline(time, 7);

    char *ptok = strtok(time, "h");
    hour = atoi(ptok);
    ptok = strtok(NULL, "h");
    min = atoi(ptok);

    int c_total = c_hour * 60 + c_min;
    int total = hour * 60 + min;
    int totalTime = abs(c_total - total);

    int cost = 0;
    while (totalTime > 60)
    {
        cost += 20;
        totalTime -= 30;
    }
    int sumPrice = 50 + cost;
    bx->tienThu += sumPrice;
    cout << "Tien gui xe: " << sumPrice << ".000vnd" << endl;
}
void traXe(BaiXe *bx, int r, int c, string id, int m)
{
    Xe **temp_xe;
    khoiTaoTempXe(temp_xe, r, c);
    char c_time[7] = "";

    //Kiem tra xe co ton tai trong bai khong
    if (isTonTai(bx, r, c, id))
    {
        //Neu tra xe thang thi khong tinh tien gui
        if (isXeThang(bx, id, m))
        {
            saoChepXe(bx, temp_xe, r, c, c_time, id);
            cout << "Tra xe thang thanh cong!!" << endl;
        }
        //Tra xe ngay & tinh tien gui
        else
        {
            saoChepXe(bx, temp_xe, r, c, c_time, id);
            tinhTienGuiXe(bx, c_time, id);
            bx->maxXeNgay++;
            cout << "Tra xe ngay thanh cong!!" << endl;
        }
    }
    else
        cout << "Xe khong ton tai trong bai!!" << endl;    
}

//Thong ke
void thongKe(BaiXe *bx, int r, int c)
{
    int count = 0;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            if (bx->xe[i][j].bienSo != "NULL")
                count++;
    }
    cout << "So luong xe dang co trong bai: " << count << endl;
    cout << "Tong tien bai: " << bx->tienThu << ".000vnd" << endl;
}

//Xuat thong tin
void output_xeThang(BaiXe *bx, int m)
{
    for (int i = 0; i < m; i++)
        cout << bx->xeThang[i].bienSo << "\t";
    cout << endl;
}
void output(BaiXe *bx, int r, int c)
{
    cout << "================================== BAI XE ==================================" << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
            cout << bx->xe[i][j].bienSo << "-" << bx->xe[i][j].loaiGui << "-" << bx->xe[i][j].thoiGianNhan << "\t";
            cout << endl;
    }
}

//Giai phong du lieu
void delete_xe(BaiXe *bx, int r)
{
    for (int i = 0; i < r; i++)
        delete[] bx->xe[i];
    delete[] bx->xe;
    bx->xe = NULL;
    cout << "Giai phong cac xe thanh cong!!" << endl;
}
void delete_xeThang(BaiXe *bx)
{
    delete[] bx->xeThang;
    bx->xeThang = NULL;
    cout << "Giai phong xe thang thanh cong!!" << endl; 
}
void delete_baiXe(BaiXe *bx)
{
    delete[] bx;
    bx = NULL;
    cout << "Giai phong bai xe thanh cong!!" << endl;
}













