//
// Created by CASPER on 20.07.2024.
//

#ifndef STRUCT_H
#define STRUCT_H
typedef struct PERSONAL {
    char name[20];
    char id[12];
}s_personal;

typedef struct Member_struct{
    char m_id[12];
    char m_name_surname[51];
    char m_gender; // E or K
    char m_dateOFbirth[9];
    char m_tel[12];
    char m_epost[51];
    char m_dateOFreg[9];
    char m_address[101];
}member_struct;
typedef struct BOOK {
    char barcode[11];
    char b_name[30];
    char author[20];
    char b_kind[30];
    int  b_stock;
}book;
typedef struct oduncKitap_struct{
    char kitap_barkod[11];
    char teslim_tarihi[9];
    char iade_tarihi[20];
    int gecikme_gun;
    int odenecek_tutar;
}odunc;
#endif //STRUCT_H
