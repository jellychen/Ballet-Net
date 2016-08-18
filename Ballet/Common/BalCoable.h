#ifndef Ballet_Common_BalCoable_H
#define Ballet_Common_BalCoable_H

namespace Ballet
{
    class BalCoable
    {
    };

    class BalNoCoable
    {
    protected:
        BalNoCoable()
        {
        }

        ~BalNoCoable()
        {
        }

    private:
        BalNoCoable(const BalNoCoable&);
        const BalNoCoable& operator=(const BalNoCoable&);
    };
}
#endif
