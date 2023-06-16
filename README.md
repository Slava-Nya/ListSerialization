# ListSerialization
Serialization and deserialization related list with random element in binary format
#### https://en.wikipedia.org/wiki/Serialization

The struct for list node has this signature:
```
struct ListNode
{
    ListNode* prev = nullptr; // pointer to the previous element of the list, or `nullptr` in case of the beginning of the list
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // a pointer to an arbitrary element of the given list, or `nullptr`
    std::string data; // arbitrary user data
};
```

Before Serialization list hexdump:
```
                Node                prev                next                rand                data
      0x600002e38210                 0x0      0x600002e38240      0x600002e382a0              1_Node
      0x600002e38240      0x600002e38210      0x600002e38270                 0x0              2_Node
      0x600002e38270      0x600002e38240      0x600002e382a0      0x600002e38240              3_Node
      0x600002e382a0      0x600002e38270      0x600002e382d0      0x600002e382d0              4_Node
      0x600002e382d0      0x600002e382a0                 0x0                 0x0              5_Node
```

Afetr Deerialization list hexdump:
```
                Node                prev                next                rand                data
      0x600002e3c030                 0x0      0x600002e30000      0x600002e30060              1_Node
      0x600002e30000      0x600002e3c030      0x600002e30030                 0x0              2_Node
      0x600002e30030      0x600002e30000      0x600002e30060      0x600002e30000              3_Node
      0x600002e30060      0x600002e30030      0x600002e30090      0x600002e30090              4_Node
      0x600002e30090      0x600002e30060                 0x0                 0x0              5_Node
