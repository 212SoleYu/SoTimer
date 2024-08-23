#include<testbench/declaration.h>

// Shared Variables
__nv uint16_t           deq_idx;
__nv uint16_t           enq_idx;
__nv uint16_t           node_idx;
__nv dijkstra_node_t    node_list[DIJKSTRA_NNODES];

__nv dijkstra_queue_t   queue[DIJKSTRA_QSIZE];
__nv uint16_t           src_node;
__nv dijkstra_queue_t   nearest_node;


void dij_main()
{
    uint16_t i;
    uint16_t cost, node, dist, nearest_dist;

    src_node = 0;
    queue[0].node = src_node;
    queue[0].dist = 0;
    queue[0].prev = DIJKSTRA_UNDEFINED;
    deq_idx = 0;
    enq_idx = 1;

    for(i = 0; i < DIJKSTRA_NNODES; ++i)
    {
        node_list[i].dist = DIJKSTRA_INFINITY;
        node_list[i].prev = DIJKSTRA_UNDEFINED;
    }

    node_list[src_node].dist = 0;
    node_list[src_node].prev = DIJKSTRA_UNDEFINED;

    Nearest_Node_Sel:
    i = deq_idx;
    if (enq_idx != i)
    {
        nearest_node.node = queue[i].node;
        nearest_node.dist = queue[i].dist;
        nearest_node.prev = queue[i].prev;

        ++i;
        if (i < DIJKSTRA_QSIZE)
            deq_idx = i;
        else
            deq_idx = 0;

        node_idx = 0;
        goto Shorter_Path_Find;
    }
    else
    {
        goto quit;
    }

    Shorter_Path_Find:
    node = nearest_node.node;
    i = node_idx;
    cost = adj_matrix[node][i];

    if (cost != DIJKSTRA_INFINITY)
    {
        nearest_dist = nearest_node.dist;
        dist = node_list[i].dist;
        if (dist == DIJKSTRA_INFINITY || dist > (cost + nearest_dist))
        {
            node_list[i].dist = nearest_dist + cost;
            node_list[i].prev = node;

            uint16_t j = enq_idx;
            queue[j].node = i;
            queue[j].dist = nearest_dist + cost;
            queue[j].prev = node;

            j++;
            if (j < DIJKSTRA_QSIZE)
                enq_idx = j;
            else
                enq_idx = 0;

        }
    }

    if(++node_idx < DIJKSTRA_NNODES)
        goto Shorter_Path_Find;
    else
        goto Nearest_Node_Sel;

    quit:
    return;
}

