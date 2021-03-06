# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")

using namespace std;
//using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef tuple<int, int, int> ti3;
typedef tuple<int, int, int, int> ti4;
typedef stack<int> si;
typedef queue<int> qi;
typedef priority_queue<int> pqi;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<ll, ll, ll, ll> tl4;
typedef stack<ll> sl;
typedef queue<ll> ql;
typedef priority_queue<ll> pql;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;

const int dx[4] = { 1,-1,0,0 };
const int dy[4] = { 0,0,1,-1 };
const int ddx[8] = { 0,0,1,1,1,-1,-1,-1 }, ddy[8] = { 1,-1,1,0,-1,1,0,-1 };
const int INF = 0x7f7f7f7f;
const ll INF_LL = 0x7f7f7f7f7f7f7f7f;
ll POW(ll a, ll b, ll MMM) { ll ret = 1; for (; b; b >>= 1, a = (a*a) % MMM)if (b & 1)ret = (ret*a) % MMM; return ret; }
ll GCD(ll a, ll b) { return b ? GCD(b, a%b) : a; }
ll LCM(ll a, ll b) { if (a == 0 || b == 0)return a + b; return a / GCD(a, b) * b; }
ll INV(ll a, ll m) {
	ll m0 = m, y = 0, x = 1;
	if (m == 1)	return 0;
	while (a > 1) {
		ll q = a / m;
		ll t = m;
		m = a % m, a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	if (x < 0) x += m0;
	return x;
}
pll EXGCD(ll a, ll b) {
	if (b == 0) return { 1,0 };
	auto t = EXGCD(b, a%b);
	return { t.second,t.first - t.second*(a / b) };
}
bool OOB(ll x, ll y, ll N, ll M) { return 0 > x || x >= N || 0 > y || y >= M; }
#define X first
#define Y second
#define rep(i,a,b) for(int i = a; i < b; i++)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int)(a.size()))
#define sf1(a) cin >> a
#define sf2(a,b) cin >> a >> b
#define sf3(a,b,c) cin >> a >> b >> c
#define sf4(a,b,c,d) cin >> a >> b >> c >> d
#define sf5(a,b,c,d,e) cin >> a >> b >> c >> d >> e
#define sf6(a,b,c,d,e,f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a,b) cout << (a) << ' ' << (b) << ' '
#define pf3(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << ' '
#define pf4(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '
#define pf5(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' '
#define pf6(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a,b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a,b,c) cout << (a) << ' ' << (b) << ' '<< (c) << '\n'
#define pf4l(a,b,c,d) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << '\n'
#define pf5l(a,b,c,d,e) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << '\n'
#define pf6l(a,b,c,d,e,f) cout << (a) << ' ' << (b) << ' '<< (c) << ' '<< (d) << ' '<< (e) << ' ' << (f) << '\n'
#define pfvec(V) for(auto const &t : V) pf1(t)
#define pfvecl(V) for(auto const &t : V) pf1(t); pf0l()
const int MX_A = 1000002;
const int MX_B = 1000002;
// 1-indexed
vi A(MX_A, -1), B(MX_B, -1), level(MX_A); // A[i],B[i] : 매칭된 상대방의 정점, level[i] : i번째 정점의 depth
vector<bool> used(MX_A); // used[i] : A_i가 매칭에 속해있는가?
vi adj[MX_A]; // adj[i] : A_i와 연결된 B들의 index
int lenA, lenB; // A의 갯수, B의 갯수
void HF_bfs() {
	qi Q;
	rep(i, 1, lenA+1) {
		if (!used[i]) {
			level[i] = 0;
			Q.push(i);
		}
		else level[i] = INF;
	}
	while (!Q.empty()) {
		int a = Q.front();
		Q.pop();
		for (auto b : adj[a]) {
			if (B[b] != -1 && level[B[b]] == INF) {
				level[B[b]] = level[a] + 1;
				Q.push(B[b]);
			}
		}
	}
}
bool HF_dfs(int a) {
	for (auto b : adj[a]) {
		if (B[b] == -1 || level[B[b]] == level[a] + 1 && HF_dfs(B[b])) {
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
int HF() {
	int match = 0;
	while (true) {
		HF_bfs();
		int flow = 0;
		rep(i, 1, lenA+1)
			if (!used[i] && HF_dfs(i)) flow++;
		if (flow == 0) break;
		match += flow;
	}
	return match;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T;
	sf1(T);
	while (T--) {
		int N, M;
		sf2(N, M);
		lenA = M;
		lenB = N;
		rep(i, 1, lenA + 1) adj[i].clear();
		fill(used.begin()+1, used.begin()+lenA+1, false);
		fill(A.begin() + 1, A.begin() + lenA+1, -1);
		fill(B.begin() + 1, B.begin() + lenB+1, -1);

		rep(i, 1, M + 1) {
			int x, y;
			sf2(x, y);
			rep(j, x, y + 1) adj[i].pb(j);
		}
		int match = HF();
		pf1l(match);
	}
}
