# ccdb
a kv db demo

### 基于B+树的kv数据库
特点：
- B+ 树
- 数据持久化
- B+树的node大小为4kb，每个node包含255条记录
- 支持页面缓存(page cache),缓存大小可设置，采用LRU淘汰算法。
- key不能重复
- key和value定长，只支持int64
- 只允许单线程访问。不支持多进程、多线程同时并发访问
- 最大支持512TB数据文件

