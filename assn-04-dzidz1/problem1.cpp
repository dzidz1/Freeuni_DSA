#include <bits/stdc++.h>
#define MAX_BOUNDARY_POINTS 2000010
#define MAX_ROCKS 30010

using namespace std;

struct Point {
  int x, y, quadrant;
  bool operator<(const Point &other) const {
    if (quadrant != other.quadrant)
      return quadrant < other.quadrant;
    return 1LL * y * other.x < 1LL * x * other.y;
  }
};

struct BlockedInterval {
  Point point;
  int block_type;

  bool operator<(const BlockedInterval &other) const {
    if (point < other.point)
      return true;
    if (other.point < point)
      return false;
    return block_type < other.block_type;
  }
};

BlockedInterval blocked_intervals[MAX_ROCKS * 2];
Point fence_posts[MAX_BOUNDARY_POINTS];
Point rock_min[MAX_ROCKS], rock_max[MAX_ROCKS];
int num_rocks, field_size, num_intervals = 0, num_fence_posts = 0;
Point farmer_position;

int calculate_quadrant(Point &p) {
  if (p.x >= 0 && p.y >= 0)
    return 0;
  if (p.x < 0 && p.y >= 0)
    return 1;
  if (p.x < 0 && p.y < 0)
    return 2;
  return 3;
}

long long cross_product(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

void process_rock_data(int rock_index, int vertices) {
  Point vertex;
  cin >> vertex.x >> vertex.y;
  vertex.x -= farmer_position.x;
  vertex.y -= farmer_position.y;
  vertex.quadrant = calculate_quadrant(vertex);

  rock_min[rock_index] = rock_max[rock_index] = vertex;

  for (int j = 1; j < vertices; j++) {
    cin >> vertex.x >> vertex.y;
    vertex.x -= farmer_position.x;
    vertex.y -= farmer_position.y;
    vertex.quadrant = calculate_quadrant(vertex);

    if (cross_product(vertex, rock_min[rock_index]) > 0) {
      rock_min[rock_index] = vertex;
    }
    if (cross_product(vertex, rock_max[rock_index]) < 0) {
      rock_max[rock_index] = vertex;
    }
  }
}

int initialize_fence_and_blocks() {
  int overlap_intervals = 0;

  for (int i = 0; i < num_rocks; ++i) {
    if (rock_min[i].quadrant > rock_max[i].quadrant) {
      overlap_intervals++;
    }
    blocked_intervals[num_intervals++] = {rock_min[i], -1};
    blocked_intervals[num_intervals++] = {rock_max[i], 1};
  }

  sort(blocked_intervals, blocked_intervals + num_intervals);

  for (int i = farmer_position.y; i <= field_size; ++i) {
    fence_posts[num_fence_posts++] = {field_size - farmer_position.x,
                                      i - farmer_position.y, 0};
    fence_posts[num_fence_posts - 1].quadrant =
        calculate_quadrant(fence_posts[num_fence_posts - 1]);
  }
  for (int i = field_size - 1; i >= 0; --i) {
    fence_posts[num_fence_posts++] = {i - farmer_position.x,
                                      field_size - farmer_position.y, 0};
    fence_posts[num_fence_posts - 1].quadrant =
        calculate_quadrant(fence_posts[num_fence_posts - 1]);
  }
  for (int i = field_size - 1; i >= 0; --i) {
    fence_posts[num_fence_posts++] = {0 - farmer_position.x,
                                      i - farmer_position.y, 0};
    fence_posts[num_fence_posts - 1].quadrant =
        calculate_quadrant(fence_posts[num_fence_posts - 1]);
  }
  for (int i = 1; i < field_size; ++i) {
    fence_posts[num_fence_posts++] = {i - farmer_position.x,
                                      0 - farmer_position.y, 0};
    fence_posts[num_fence_posts - 1].quadrant =
        calculate_quadrant(fence_posts[num_fence_posts - 1]);
  }
  for (int i = 0; i < farmer_position.y; ++i) {
    fence_posts[num_fence_posts++] = {field_size - farmer_position.x,
                                      i - farmer_position.y, 0};
    fence_posts[num_fence_posts - 1].quadrant =
        calculate_quadrant(fence_posts[num_fence_posts - 1]);
  }

  return overlap_intervals;
}

int count_visible_fence_posts(int overlap_count) {
  int active_blocks = -overlap_count;
  int visible_count = 0;
  int interval_index = 0;

  for (int i = 0; i < num_fence_posts; ++i) {
    while (interval_index < num_intervals &&
           blocked_intervals[interval_index] <
               BlockedInterval{fence_posts[i], 0}) {
      active_blocks += blocked_intervals[interval_index++].block_type;
    }
    if (active_blocks == 0) {
      visible_count++;
    }
  }

  return visible_count;
}

int main() {
  cin >> field_size >> num_rocks;
  cin >> farmer_position.x >> farmer_position.y;
  farmer_position.quadrant = -1;

  for (int i = 0; i < num_rocks; ++i) {
    int vertices;
    cin >> vertices;
    process_rock_data(i, vertices);
  }

  int overlap_count = initialize_fence_and_blocks();

  cout << count_visible_fence_posts(overlap_count) << endl;
  return 0;
}