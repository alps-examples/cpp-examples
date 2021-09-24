

int main() {
  // Finally we can use ' to split long numbers
  static_assert(0x0098'96AA == 10'000'042);

  // .. but we can do it weirdly, too
  static_assert(0x0098'96AA == 1'0000'04'2);

  // By the way, 052 is the octal representation of 42
  static_assert(052 == 42);
}
