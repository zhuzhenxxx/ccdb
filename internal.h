#ifndef __cc_intern_h__
#define __cc_intern_h__

#include <stdint.h>
#include <unistd.h>

#define PAGE_SIZE 4096ULL                                    //页大小 4KB
#define FILE_META_LEN      (2 * 1024 * 1024ULL)              //file header  包括1MB metadata 和1MB busy page number
#define BUSY_PAGE_NUM_POS  (1 * 1024 * 1024ULL)              //1MB 每个chunk占用4bytes，表示这个chunk里面已被占用了的page的数量
#define PAGE_BITMAP_LEN    (64 * 1024ULL)                    //64KB 用来记录page使用情况。 最大支持：256K个chunk
#define PAGE_BITMAP_PAGES  (PAGE_BITMAP_LEN/PAGE_SIZE)       //page页数
#define PAGE_NUM_PER_CHUNK (PAGE_BITMAP_LEN*8)               //
#define PAGE_BITMAP_WLEN   (64 * 1024ULL/8)                  //字节数
#define MAX_CHUNK_NUM      (256 * 1024ULL)                   //256K
#define CHUNK_DATA_LEN     (PAGE_BITMAP_LEN * 8 * PAGE_SIZE) //chunk数据长度 
#define DATA_AREA_LEN      (MAX_CHUNK_NUM * CHUNK_DATA_LEN)  //整个数据区长度


typedef uint64_t gpid_t;  //全局 pageid
#define GPID_NIL ((gpid_t)-1)

//单个记录 key:value
struct record_s {
    uint64_t key;
    uint64_t value;
};

#define PAGE_LEAF (1<<0)

//page在文件中布局  [ header rec rec rec ........rec ]
//                      |                         | 
//                 [record_num flags  next]     [key value]     
struct page_header_s {
    int32_t record_num;
    uint32_t flags;
    gpid_t next;
};

struct page_s {
    struct page_header_s head;
    struct record_s      rec[RECORD_NUM_PG];
};


//整个文件内的存储结构
struct file_header_s {
    uint64_t magic;
    uint64_t file_size;
    uint64_t record_num;
    uint64_t total_pages;
    uint64_t spare_pages;
    uint64_t level;
    uint32_t reserve;
    gpid_t   root_gpid;
};

struct busy_page_num_s {
    uint32_t n[MAX_CHUNK_NUM];
};



#endif
