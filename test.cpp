#include "ListSerialization.h"
#include <cstdio>
#include <iomanip>

void printList(const List *list)
{
    auto tmp = list->getHead();
    auto count = list->getCount();

    std::cout << std::setw(20) << "Node";
    std::cout << std::setw(20) << "prev";
    std::cout << std::setw(20) << "next";
    std::cout << std::setw(20) << "rand";
    std::cout << std::setw(20) << "data";
    std::cout << std::endl;

    for (auto i = 0; i < count; ++i)
    {
        std::cout << std::setw(20) << tmp;
        std::cout << std::setw(20) << tmp->prev;
        std::cout << std::setw(20) << tmp->next;
        std::cout << std::setw(20) << tmp->rand;
        std::cout << std::setw(20) << tmp->data;
        std::cout << std::endl;

        tmp = tmp->next;
    }
    std::cout << "\n ----------------------------- \n "<< std::endl;
}

void deleteList(List *list)
{
    auto *node = list->getHead();
    auto count = list->getCount();
    ListNode *tmp;

    for (auto i = 0; i < count; ++i)
    {
        tmp = node->next;
        delete node;
        node = tmp;
    }
}

int main()
{
    List testList;

    auto *node1 = new ListNode; node1->data = "1_Node";
    auto *node2 = new ListNode; node2->data = "2_Node";
    auto *node3 = new ListNode; node3->data = "3_Node";
    auto *node4 = new ListNode; node4->data = "4_Node";
    auto *node5 = new ListNode; node5->data = "5_Node";

    node1->rand = node4;
    node3->rand = node2;
    node4->rand = node5;

    testList.setTailNode(node1);
    testList.setTailNode(node2);
    testList.setTailNode(node3);
    testList.setTailNode(node4);
    testList.setTailNode(node5);

    FILE *fp;
    {
        if ((fp = fopen("test.bin", "wb")) == nullptr) {
            printf("Cannot open file.\n");
            exit(1);
        }
        testList.Serialize(fp);
        fclose(fp);

        std::cout << "Before serialize" << std:: endl;
        printList(&testList);
    }
    {
        if ((fp = fopen("test.bin", "rb")) == nullptr) {
            printf("Cannot open file.\n");
            exit(1);
        }
        List list;
        list.Deserialize(fp);
        fclose(fp);

        std::cout << "After deserialize" << std:: endl;
        printList(&list);
        deleteList(&list);
    }
    deleteList(&testList);

    return 0;
}