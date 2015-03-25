#ifndef SETTINGS_H
#define SETTINGS_H
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <map>

class EmptyProperty  : public std::exception{
public:
    EmptyProperty(const std::string & name)throw():error_message("Trying to cast empty property: " + name + "."){}
    virtual const char* what()const throw(){return error_message.c_str();}
    ~EmptyProperty()throw(){}
private:
    std::string error_message;
};

class settings {
    public:
        class param {
            friend class settings;
            private:
                param(param const &);
                param(const std::string & name, std::string value, settings *owner, bool empty = false);
                std::string value;
                std::string name;
                bool isEmpty;
                settings *owner;
            public:
                operator std::string() const;
                operator int() const;
                operator bool() const;
                operator double() const;

                param & operator=(std::string const &);
                param & operator=(const char*);
                param & operator=(int);
                param & operator=(bool);
                param & operator=(double);

                param & operator+=(std::string const &);
                param & operator+=(int);
                param & operator+=(double);

                param & operator-=(int);
                param & operator-=(double);

                param & operator*=(int);
                param & operator*=(double);

                param & operator/=(int);
                param & operator/=(double);

                param & operator|=(bool);
                param & operator&=(bool);
                bool is_empty() const;
        };

        // Main functions

        friend class param;

        /**
         * Construct settings store
         * and load data from file (if exists)
         * \param filename Path to file with settings
         */
        settings(std::string const & filename);
        /**
         * Get setting value
         * \param name Setting unique identifier
         * \param def Default setting value
         * \return Stored value for given name or default value
         */
        std::string const & get(std::string const & name,
            std::string const & def = "") const;
        /**
         * Set or replace setting value and save changes to file
         * \param name Setting unique identifier
         * \param value New setting value
         */
        void set(std::string const & name,
            std::string const & value);
        /**
         * Reset all settings
         */
        void reset();
        /**
         * Reload all settings from file
         */
        void reload();

        // Advanced funсtions

        /**
          * Get constant setting wrapper
          * \param name Setting unique identifier
          */
        const param operator[](std::string const & name) const;
        /**
          * Get constant setting wrapper
          * \param name Setting unique identifier
          */
        param operator[](std::string const & name);

private:
        void sync(std::string &name, std::string &value);
        void sync();
        std::string filename;
        std::map<std::string, std::string> list;
};


#endif // SETTINGS_H
