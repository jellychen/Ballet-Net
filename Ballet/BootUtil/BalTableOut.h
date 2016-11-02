#ifndef Ballet_BootUtil_BalTableOut_H
#define Ballet_BootUtil_BalTableOut_H
#include "Common/BalInct.h"

namespace Ballet
{
    namespace BootUtil
    {
        class BalTableOut: public BalNoCoable
        {
        public:
            BalTableOut(uint16_t column)
            {
                column_ = column;
            }

        public:
            void SetTitle(std::vector<std::string> title)
            {
                title_.clear(); uint16_t i = 0;
                for (; i < (uint16_t)title.size() && i < column_; ++i)
                {
                    title_.push_back(title[i]);
                }
            }

            void AddRow(std::vector<std::string> row)
            {
                rowsData_.push_back(row);
            }

            void DumpOut()
            {
                if (0 == column_) return;

                std::vector<int> outWidth;
                for (size_t i = 0; i < (size_t)column_; ++i)
                {
                    int maxWidth = 1;
                    for (size_t j = 0; j < rowsData_.size(); ++j)
                    {
                        if (rowsData_[j].size() > i && rowsData_[j][i].length() > maxWidth)
                        {
                            maxWidth = rowsData_[j][i].length();
                        }
                    }

                    if (i != column_ - 1)
                    {
                        outWidth.push_back(maxWidth + 5);
                    }
                    else
                    {
                        outWidth.push_back(maxWidth);
                    }
                }

                for (size_t i = 0; i < title_.size() && i < (size_t)column_; ++i)
                {
                    if (i != column_ - 1)
                    {
                        if (title_[i].length() + 5 > outWidth[i])
                        {
                            outWidth[i] = title_[i].length() + 5;
                        }
                    }
                    else
                    {
                        if (title_[i].length() > outWidth[i])
                        {
                            outWidth[i] = title_[i].length();
                        }
                    }
                }

                std::cout<<std::endl;
                for (size_t i = 0; i < title_.size() && i < (size_t)column_; ++i)
                {
                    std::cout <<std::left <<std::setw(outWidth[i]) <<title_[i];
                }

                std::cout<<std::endl;
                for (size_t i = 0; i < outWidth.size(); ++i)
                {
                    for (size_t j = 0; j < outWidth[i]; ++j)
                    {
                        std::cout<<"-";
                    }
                }

                std::cout<<std::endl;
                for (size_t i = 0; i < rowsData_.size(); ++i)
                {
                    std::vector<std::string>& row = rowsData_[i];
                    for (size_t j = 0; j < row.size() && j < (size_t)column_; ++j)
                    {
                        std::cout <<std::left <<std::setw(outWidth[j]) <<row[j];
                    }
                    std::cout<<std::endl;
                }
                std::cout<<std::endl;
                rowsData_.clear(); title_.clear();
            }

        private:
            uint16_t column_;
            std::vector<std::string> title_;
            std::vector<std::vector<std::string> > rowsData_;
        };
    }
}
#endif
