#ifndef VTMAPS_SINGLETON_H
#define VTMAPS_SINGLETON_H

#define LAZY_SINGLETON(type_name) \
        public:\
            static type_name& instance() {\
                static type_name instance;\
                return instance;\
            };\
        private:\
            type_name(const type_name& obj) = delete;\
            void operator=(const type_name& obj) = delete;\
            type_name() = default;



#define EAGER_SINGLETON(type_name) \
        public: \
            static type_name& instance() { \
                return _instance; \
            } \
        private: \
            static type_name _instance; \
            type_name(const type_name& obj) = delete; \
            void operator=(const type_name& obj) = delete; \
            type_name() = default;

#endif //VTMAPS_SINGLETON_H
