

class Static {
public:
    static int bar() { return 1; }
};

int main() {
    int i = 0;
    i++;
    Static::bar();
}
