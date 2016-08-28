#ifndef Ballet_Common_BalVariable_H
#define Ballet_Common_BalVariable_H

namespace Ballet
{
    template<class T, class U> class BalVariable
    {
    public:
        explicit BalVariable(T& data, U var)
        {
        }

        ~BalVariable()
        {
        }
    private:
        T& data_; T oldData_;
    };
}
#endif
