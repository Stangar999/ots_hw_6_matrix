#include <set>
#include <unordered_map>

template <typename T, T default_val>
class Matrix {
  /// структура для объединения индексов строк и колонок в матрице
  struct Index {
    size_t col = 0;
    size_t row = 0;
    friend bool operator<(const Index& lth, const Index& rth) {
      return std::tuple{lth.col, lth.row} < std::tuple{rth.col, rth.row};
    }
    friend bool operator==(const Index& lth, const Index& rth) {
      return std::tuple{lth.col, lth.row} == std::tuple{rth.col, rth.row};
    }
    struct Hash {
      size_t operator()(const Index& index) const {
        return std::hash<size_t>{}(index.col) +
               37ull * std::hash<size_t>{}(index.row);
      }
    };
  };

  /// контейнер самих значений по ключу Index
  std::unordered_map<Index, T, typename Index::Hash> _container;
  /// список индексов в отсортированом порядке для правильной итерации по
  /// строкам
  std::set<Index> _indexes;

 public:
  class SubValue {
    Matrix& _matrix;
    T _value;
    Index _indx;

   public:
    SubValue(Matrix& matrix, size_t c, size_t r)
        : _matrix(matrix),
          _indx(Index{.col = c, .row = r}),
          _value(default_val) {
      if (_matrix._indexes.count(_indx)) {
        _value = _matrix._container[_indx];
      }
    }

    SubValue& operator=(const T& t) {
      if (t != default_val) {
        _matrix._indexes.insert(_indx);
        _matrix._container[_indx] = t;
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
  template <typename It>
  class Iterator : public std::iterator_traits<It> {
    friend class Matrix;
    Matrix& _matrix;
    It _it;
    Iterator(Matrix& matrix, It it)
        : _matrix(matrix),
          _it(it){};

   public:
    Iterator& operator++() {
      if (_it == _matrix._indexes.end()) {
        return *this;
      }
      ++_it;
      return *this;
    }

    std::tuple<size_t, size_t, T> operator*() {
      return {_it->col, _it->row, _matrix._container[*_it]};
    }

    bool operator!=(const Iterator& other) {
      return other._it != _it;
    }
  };

  Matrix(){};

  size_t size() const {
    size_t size = 0;
    return _container.size();
  }

  SubMatrix operator[](size_t c) {
    return {*this, c};
  }

  auto begin() {
    return Iterator<typename std::set<Index>::iterator>(*this,
                                                        _indexes.begin());
  }

  auto end() {
    return Iterator<typename std::set<Index>::iterator>(*this, _indexes.end());
  }
};
