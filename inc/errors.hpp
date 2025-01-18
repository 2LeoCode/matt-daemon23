#ifndef ERRORS_H
#define ERRORS_H

struct PermissionError {
  const char *what() const noexcept;
};

#endif // !ERRORS_H
