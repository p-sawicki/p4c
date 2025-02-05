#include <core.p4>

extern E {
    E(list<bit<32>> data);
    void run();
}

control c() {
    E((list<bit<16>>){ 2, 3, 4 }) e;
    apply {
        e.run();
    }
}

control C();
package top(C _c);
top(c()) main;

