Element();

    Element(const Element& other);

    template<typename U>
    Element(const Element<S, U>& other);

    template<typename OtherS, typename U>
    Element(const Element<OtherS, U>& other);

    Element(const T& other);

    template<typename U>
    Element(const U& other);

    explicit Element(const S& set);

    Element(const S& set, const T& other);

    template<typename U>
    Element(const S& set, const U& other);

    template<typename OtherS, typename U>
    Element(const S& set, const Element<OtherS, U>& other);
