// Modular lazy segment tree
// It takes a type T for vertex values and a type U for update
// operations. Type T should have an operator '+' specifying how to
// combine vertices. Type U should have an operator '()' specifying how
// to apply updates to vertices and an operator '+' for combining two
// updates. Example below.
template<typename T, typename U> struct seg_tree_lazy {
    int S, H;
    T zero;
    vector<T> value;
    U noop;
    vector<bool> dirty;
    vector<U> prop;

    seg_tree_lazy<T, U>(int _S, T _zero = T(), U _noop = U()) {
        zero = _zero, noop = _noop;
        for (S = 1, H = 1; S < _S; ) S *= 2, H++;
        value.resize(2*S, zero);
        dirty.resize(2*S, false);
        prop.resize(2*S, noop);
    }
    void set_leaves(vector<T> &leaves) {
        copy(leaves.begin(), leaves.end(), value.begin() + S);
        for (int i = S - 1; i > 0; i--)
            value[i] = value[2 * i] + value[2 * i + 1];
    }
    void apply(int i, U &update) {
        value[i] = update(value[i]);
        if(i < S) {
            prop[i] = prop[i] + update;
            dirty[i] = true;
        }
    }
    void rebuild(int i) {
        for (int l = i/2; l; l /= 2) {
            T combined = value[2*l] + value[2*l+1];
            value[l] = prop[l](combined);
        }
    }
    void propagate(int i) {
        for (int h = H; h > 0; h--) {
            int l = i >> h;
            if (dirty[l]) {
                apply(2*l, prop[l]);
                apply(2*l+1, prop[l]);
                prop[l] = noop;
                dirty[l] = false;
            }
        }
    }
    void upd(int i, int j, U update) {
        i += S, j += S;
        propagate(i), propagate(j);
        for (int l = i, r = j; l <= r; l /= 2, r /= 2) {
            if((l&1) == 1) apply(l++, update);
            if((r&1) == 0) apply(r--, update);
        }
        rebuild(i), rebuild(j);
    }
    T query(int i, int j){
        i += S, j += S;
        propagate(i), propagate(j);
        T res_left = zero, res_right = zero;
        for(; i <= j; i /= 2, j /= 2){
            if((i&1) == 1) res_left = res_left + value[i++];
            if((j&1) == 0) res_right = value[j--] + res_right;
        }
        return res_left + res_right;
    }
};

// Example that supports following operations:
// 1: Add amount V to the values in range [L,R].
// 2: Reset the values in range [L,R] to value V.
// 3: Query for the sum of the values in range [L,R].

// Here's what T looks like:
struct node {
    int sum, width;
    node operator+(const node &n) {
        return { sum + n.sum, width + n.width }
    }
};
// Here's what U looks like:
struct update {
    bool type; // 0 for add, 1 for reset
    int value;
    node operator()(const node &n) {
        if(type) return { n.width * value, n.width };
        else return { n.sum + n.width * value, n.width };
    }
    update operator+(const update &u) {
        if(u.type) return u;
        return { type, value + u.value };
    }
};
int main() {
    int N = 100;
    node zero = {0,0};
    update noop = {false, 0};
    vector<node> leaves(N, {0,1});
    seg_tree_lazy<node, update> st(N, zero, noop);
    st.set_leaves(leaves);
}
