zskiplistNode *zslInsert(zskiplist *zsl, double score, sds ele)
{
    // 存储搜索路径
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    // 存储经过的节点跨度
    unsigned int rank[ZSKIPLIST_MAXLEVEL];
    int i, level;
    serverAssert(!isnan(score));
    x = zsl->header;
    // 逐步降级寻找目标节点，得到「搜索路径」
    for (i = zsl->level - 1; i >= 0; i--)
    {
        /* store rank that is crossed to reach the insert position */
        rank[i] = i == (zsl->level - 1) ? 0 : rank[i + 1];
        // 如果 score 相等，还需要比较 value
        while (x->level[i].forward &&
               (x->level[i].forward->score < score ||
                (x->level[i].forward->score == score &&
                 sdscmp(x->level[i].forward->ele, ele) < 0)))
        {
            rank[i] += x->level[i].span;
            第 210 页 共 226 页
                    Redis 深度历险：核心原理与应用实践 |
                钱文品 著
                    x = x->level[i].forward;
        }
        update[i] = x;
    }
    // 正式进入插入过程
    /* we assume the element is not already inside, since we allow duplicated
* scores, reinserting the same element should never happen since the
* caller of zslInsert() should test in the hash table if the element is
* already inside or not. */
    // 随机一个层数
    level = zslRandomLevel();
    // 填充跨度
    if (level > zsl->level)
    {
        for (i = zsl->level; i < level; i++)
        {
            rank[i] = 0;
            update[i] = zsl->header;
            update[i]->level[i].span = zsl->length;
        }
        // 更新跳跃列表的层高
        zsl->level = level;
    }
    // 创建新节点
    x = zslCreateNode(level, score, ele);
    // 重排一下前向指针
    for (i = 0; i < level; i++)
    {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;
        /* update span covered by update[i] as x is inserted here */
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }
    /* increment span for untouched levels */
    for (i = level; i < zsl->level; i++)
    {
        update[i]->level[i].span++;
    }
    // 重排一下后向指针
    x->backward = (update[0] == zsl->header) ? NULL : update[0];
    if (x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        zsl->tail = x;
    zsl->length++;
    return x;
}