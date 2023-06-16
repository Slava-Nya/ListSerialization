#ifndef LISTSERIALIZATION_H
#define LISTSERIALIZATION_H

#include <iostream>
#include <unordered_map>

struct ListNode
{
    ListNode* prev = nullptr; // pointer to the previous element of the list, or `nullptr` in case of the beginning of the list
    ListNode* next = nullptr;
    ListNode* rand = nullptr; // a pointer to an arbitrary element of the given list, or `nullptr`
    std::string data; // arbitrary user data
};

class List {
public:

    void setTailNode(ListNode *node) {
        if (!count) {
            head = node;
            tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        ++count;
    }

    ListNode* getHead() const{
        return (head);
    }

    auto getCount() const{
        return (count);
    }

    void Serialize(FILE *file) // saving the list to a file, the file is opened with `fopen(path, "wb")`
    {
        fwrite( &count, sizeof(this->count), 1, file);

        ListNode *currentNode = head;
        for (auto i = 0; i < count; i++) {
            fwrite((char *) &currentNode, sizeof(&currentNode), 1, file);
            fwrite((char *) &currentNode->rand, sizeof(&currentNode->rand), 1, file);

            size_t dataLen = currentNode->data.size() + 1;
            std::fwrite(&dataLen, sizeof(size_t), 1, file);
            std::fwrite((char *) &currentNode->data, sizeof(char) * dataLen, 1, file);

            currentNode = currentNode->next;
        }
    }

    void Deserialize(FILE *file)
    {
        auto listCount = 0;
        fread( &listCount, sizeof(listCount), 1, file);

        std::unordered_map<ListNode * /* nodeOldAddr */, ListNode * /* nodeNewAddr */> addrMap(listCount);

        for (auto i = 0; i < listCount; i++) {
            auto currentNode = new ListNode();
            size_t len = 0;
            ListNode *nodeOldAddr, *randOldAddr;

            fread((char *) &nodeOldAddr, sizeof(nodeOldAddr), 1, file);
            fread((char *) &randOldAddr, sizeof(randOldAddr), 1, file);
            fread(&len, sizeof(size_t), 1, file);
            fread((char *) &currentNode->data, len * sizeof(char), 1, file);

            currentNode->rand = randOldAddr;
            addrMap[nodeOldAddr] = currentNode;

            setTailNode(currentNode);
        }

        ListNode *el = head;
        for (auto i = 0; i < count; i++)
        {
            if (el->rand)
                el->rand = addrMap.find(el->rand)->second;
            el = el->next;
        }
    }

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    int count = 0;
};

#endif //LISTSERIALIZATION_H
