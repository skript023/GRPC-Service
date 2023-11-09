#pragma once
#include "common.hpp"

struct Activities
{
    int id;
    std::string name;
    std::string start_date;
    std::string end_date;
    std::string status;

    bool operator==(std::unique_ptr<Activities, std::default_delete<Activities>> activity)
    {
        return activity->name == this->name && activity->start_date == this->start_date && activity->end_date == this->end_date;
    }
    bool operator!=(std::unique_ptr<Activities, std::default_delete<Activities>> activity)
    {
        return activity->name != this->name && activity->start_date != this->start_date && activity->end_date != this->end_date;
    }
    bool operator==(Activities activity)
    {
        return activity.name == this->name || activity.start_date == this->start_date || activity.end_date == this->end_date;
    }
    bool operator!=(Activities activity)
    {
        return activity.name != this->name || activity.start_date != this->start_date || activity.end_date != this->end_date;
    }
};
