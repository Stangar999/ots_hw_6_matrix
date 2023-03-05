#include <unordered_map>

template <typename T, T default_val>
class Matrix {
  typedef std::unordered_map<size_t, T> VC;
  std::unordered_map<size_t, VC> _container;

 public:
  Matrix(){};

  int size() const {
    size_t size = 0;
    for (const auto& [key, vc] : _container) {
      size += vc.size();
    }
    return size;
  }

  class SubValue {
    Matrix& _matrix;
    T _value;
    size_t _c;
    size_t _r;

   public:
    SubValue(Matrix& matrix, size_t c, size_t r)
        : _matrix(matrix),
          _c(c),
          _r(r),
          _value(default_val) {
      if (_matrix._container.count(c)) {
        if (_matrix._container[c].count(r)) {
          _value = _matrix._container[c][r];
        }
      }
    }

    SubValue& operator=(const T& t) {
      if (t != default_val) {
        _matrix._container[_c][_r] = t;
      }
      return *this;
    }

    operator T() {
      return _value;
    }
  };

  class SubMatrix {
    Matrix& _matrix;
    size_t _c;

   public:
    SubValue operator[](size_t r) {
      return {_matrix, _c, r};
    }

    SubMatrix(Matrix& matrix, size_t c)
        : _matrix(matrix),
          _c(c){};
  };

  SubMatrix operator[](size_t c) {
    return {*this, c};
  }

  // template<typename IT>
  class Iterator /*: public std::iterator_traits<IT>*/ {
    friend class Matrix;
    Matrix& _matrix;
    using It_c =
        typename std::unordered_map<size_t,
                                    std::unordered_map<size_t, int>>::iterator;
    using It_r = typename std::unordered_map<size_t, int>::iterator;
    It_c _it_c;
    It_r _it_r;
    Iterator(Matrix& matrix, It_c it_c)
        : _matrix(matrix),
          _it_c(it_c) {
      if (_it_c != _matrix._container.end()) {
        _it_r = _it_c->second.begin();
      }
    };

   public:
    Iterator& operator++() {
      if (_it_c == _matrix._container.end()) {
        return *this;
      }
      ++_it_r;
      if (_it_r == _it_c->second.end()) {
        ++_it_c;
        if (_it_c == _matrix._container.end()) {
          return *this;
        }
        _it_r = _it_c->second.begin();
      }
      return *this;
    }

    std::tuple<size_t, size_t, T> operator*() {
      return {_it_c->first, _it_r->first, _it_r->second};
    }

    bool operator!=(Iterator other) {
      if (other._it_c == _matrix._container.end() &&
          _it_c == _matrix._container.end()) {
        return false;
      }
      return other._it_c != _it_c || other._it_r != _it_r;
    }
  };

  auto begin() {
    return Iterator(*this, _container.begin());
  }

  auto end() {
    return Iterator(*this, _container.end());
  }
};
