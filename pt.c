#include "os.h"

#define ENTRY_COUNT 512
#define VALID_BIT (1ULL << 0)
#define ADDR_MASK (~(VALID_BIT))
#define BITS_PER_LEVEL 9
#define LEVEL_MASK ((1ULL << BITS_PER_LEVEL) - 1)
#define LEVEL_NUM 5

typedef struct
{
    uint64_t entries[ENTRY_COUNT];
} page_table_node;

page_table_node *allocate_page_table_node()
{
    uint64_t frame = alloc_page_frame();
    return (page_table_node *)phys_to_virt(frame << 12);
}

uint64_t get_level_bits(uint64_t vpn, int level)
{
    return (vpn >> (level * BITS_PER_LEVEL)) & LEVEL_MASK;
}

void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn)
{
    page_table_node *node = phys_to_virt(pt << 12);
    for (int i = LEVEL_NUM - 1; i >= 0; i--)
    {
        uint64_t entry = get_level_bits(vpn, i);
        if (i == 0)
        {
            if (ppn == NO_MAPPING)
                node->entries[entry] = 0;
            else
                node->entries[entry] = (ppn << 12) | VALID_BIT;
            return;
        }
        if ((node->entries[entry] & VALID_BIT) == 0)
        {
            if (ppn == NO_MAPPING)
                return;
            uint64_t new_page = alloc_page_frame();
            node->entries[entry] = (new_page << 12) | VALID_BIT;
        }
        node = phys_to_virt(node->entries[entry] & ADDR_MASK);
    }
}

uint64_t page_table_query(uint64_t pt, uint64_t vpn)
{
    page_table_node *node = phys_to_virt(pt << 12);
    for (int i = LEVEL_NUM - 1; i >= 0; i--)
    {
        uint64_t entry = get_level_bits(vpn, i);
        if ((node->entries[entry] & VALID_BIT) == 0)
            return NO_MAPPING;
        if (i == 0)
            return node->entries[entry] >> 12;
        node = phys_to_virt(node->entries[entry] & ADDR_MASK);
    }
    return NO_MAPPING;
}