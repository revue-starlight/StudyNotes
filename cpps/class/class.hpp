class coor{
    private:
    int page;
    int time;
    public:
    coor();
    ~coor();
    coor(const coor &from);
    coor& operator=(const coor &from);
    friend coor operator+(const int page,const coor& book);
};