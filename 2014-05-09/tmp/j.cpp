#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

const double EPS = 1E-9;

struct Point {
  double x,y;
  Point(double x_ = 0, double y_ = 0):
      x(x_),
      y(y_) { }
};

struct Line {
  Point a,b;
};

struct Rect {
  Point a,b,c,d;
};

Point operator - (const Point &a, const Point &b) {
  return Point(a.x-b.x, a.y-b.y);
}

double Abs(double a) {
  return a > 0? a : -a;
}

bool DoubleEq(double a, double b) {
  return Abs(a-b) < EPS;
}

double Angle(const Point &p) {
  return atan2(p.x, p.y);
}

bool PointBetween(const Point &f, const Point &a, const Point &b, bool border) {
  if (border) {
    if (((f.x < a.x + EPS && f.x > b.x - EPS) ||
         (f.x < b.x + EPS && f.x > a.x - EPS)) &&
        ((f.y < a.y + EPS && f.y > b.y - EPS) ||
         (f.y < b.y + EPS && f.y > a.y - EPS))) {
      return true;
    }
  } else {
    if (((f.x < a.x - EPS && f.x > b.x + EPS) ||
         (f.x < b.x - EPS && f.x > a.x + EPS) ||
          DoubleEq(a.x, b.x)) &&
        ((f.y < a.y - EPS && f.y > b.y + EPS) ||
         (f.y < b.y - EPS && f.y > a.y + EPS) ||
          DoubleEq(a.y, b.y))) {
      return true;
    }
  }
  return false;
}

vector<int> rsq;
int shift = 0;

void CreateRSQ(int n) {
  int st = 1;
  while (st < 2*n) {
    st *= 2;
  }
  rsq.assign(st + 1, 0);
  shift = st/2;
}

void Update(int i, int value) {
  int index = shift + i;
  while (index != 0) {
    rsq[index] += value;
    index /= 2;
  }
}

int recSum(int l, int r) {
  if (l == r) {
    return rsq[l];
  }
  if (l % 2 == 1) {
    return rsq[l] + recSum(l + 1, r);
  }
  if (r % 2 == 0) {
    return rsq[r] + recSum(l, r - 1);
  }
  return recSum(l / 2, r / 2);
}

int Sum(int l, int r) {
  l = shift + l;
  r = shift + r;
  return recSum(l, r);
}

bool SegmentIntersect(const Line &line, 
                      const Point &a,
                      const Point &b,
                      bool border,
                      Point *f) {
  double alpha_line = line.a.y - line.b.y;
  double beta_line = -(line.a.x - line.b.x);
  double gamma_line = line.b.x * (line.a.y - line.b.y) 
                    - line.b.y * (line.a.x - line.b.x);
  double alpha_seg = a.y - b.y;
  double beta_seg = -(a.x - b.x);
  double gamma_seg = b.x * (a.y - b.y) 
                   - b.y * (a.x - b.x);

  if (DoubleEq(alpha_line * beta_seg, alpha_seg * beta_line)) {
    return false;
  }

  if (DoubleEq(alpha_seg, 0.0)) {
    swap(alpha_seg, alpha_line);
    swap(beta_seg, beta_line);
    swap(gamma_seg, gamma_line);
  }

  f->y = (gamma_line * alpha_seg - gamma_seg * alpha_line) 
       / (beta_line * alpha_seg - beta_seg * alpha_line);  
  f->x = (gamma_seg - beta_seg * f->y)
       / (alpha_seg);

  if (PointBetween(*f, a, b, border)) {
    return true;
  }
  return false;
}

bool RectIntersect(const Line &line, 
                   const Rect& rect,
                   Point *f,
                   Point *s) {
  Point *curr = f;
  int points_count = 0;
  if (SegmentIntersect(line, rect.a, rect.b, true, curr)) {
    curr = s;
    ++points_count;
  }
  if (SegmentIntersect(line, rect.b, rect.c, false, curr)) {
    curr = s;
    ++points_count;
  }
  if (points_count < 2 && SegmentIntersect(line, rect.c, rect.d, true, curr)) {
    curr = s;
    ++points_count;
  }
  if (points_count < 2 && SegmentIntersect(line, rect.d, rect.a, false, curr)) {
    curr = s;
    ++points_count;
  }
  return points_count == 2;
}


int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);

  int lines_count = 0;
  cin >> lines_count;
  vector<Line> lines(lines_count);
  for (int i = 0; i < lines_count; ++i) {
    scanf("%lg %lg %lg %lg", &(lines[i].a.x), &(lines[i].a.y), &(lines[i].b.x), &(lines[i].b.y));
    //cin >> lines[i].a.x >> lines[i].a.y >> lines[i].b.x >> lines[i].b.y;
  }
  Rect rect;
  cin >> rect.a.x >> rect.a.y;
  cin >> rect.b.x >> rect.b.y;
  cin >> rect.c.x >> rect.c.y;
  cin >> rect.d.x >> rect.d.y;
  Point center =  Point((rect.a.x + rect.b.x + rect.c.x + rect.d.x) / 4, 
                        (rect.a.y + rect.b.y + rect.c.y + rect.d.y) / 4); 

  vector< pair<double, int> > points;

  for (int i = 0; i < lines_count; ++i) {
    Point f, s;
    if (RectIntersect(lines[i], rect, &f, &s)) {
      points.push_back(make_pair(Angle(f - center), i));
      points.push_back(make_pair(Angle(s - center), i));
    }
  }
 
  sort(points.begin(), points.end());

  CreateRSQ(points.size());

  long long answer = 0;
  vector<int> positions(lines_count, -1);
  for (size_t i = 0; i < points.size(); ++i) {
    if (positions[points[i].second] == -1) {
      Update(i, +1);
      positions[points[i].second] = i;
    } else {
      Update(positions[points[i].second], -1);
      answer += Sum(positions[points[i].second], i);
      positions[points[i].second] = -1;
    }
  }
  
  cout << answer << endl;

  return 0;
}