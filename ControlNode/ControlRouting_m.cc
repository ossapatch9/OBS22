//
// Generated file, do not edit! Created by nedtool 4.6 from CoreNode/CoreRouting.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CoreRouting_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(CoreRouting);

CoreRouting::CoreRouting() : ::cObject()
{
    this->outPort_var = -1;
    this->outLabel_var = -1;
    this->outColor_var = -1;
}

CoreRouting::CoreRouting(const CoreRouting& other) : ::cObject(other)
{
    copy(other);
}

CoreRouting::~CoreRouting()
{
}

CoreRouting& CoreRouting::operator=(const CoreRouting& other)
{
    if (this==&other) return *this;
    ::cObject::operator=(other);
    copy(other);
    return *this;
}

void CoreRouting::copy(const CoreRouting& other)
{
    this->outPort_var = other.outPort_var;
    this->outLabel_var = other.outLabel_var;
    this->outColor_var = other.outColor_var;
}

void CoreRouting::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->outPort_var);
    doPacking(b,this->outLabel_var);
    doPacking(b,this->outColor_var);
}

void CoreRouting::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->outPort_var);
    doUnpacking(b,this->outLabel_var);
    doUnpacking(b,this->outColor_var);
}

int CoreRouting::getOutPort() const
{
    return outPort_var;
}

void CoreRouting::setOutPort(int outPort)
{
    this->outPort_var = outPort;
}

int CoreRouting::getOutLabel() const
{
    return outLabel_var;
}

void CoreRouting::setOutLabel(int outLabel)
{
    this->outLabel_var = outLabel;
}

int CoreRouting::getOutColor() const
{
    return outColor_var;
}

void CoreRouting::setOutColor(int outColor)
{
    this->outColor_var = outColor;
}

class CoreRoutingDescriptor : public cClassDescriptor
{
  public:
    CoreRoutingDescriptor();
    virtual ~CoreRoutingDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CoreRoutingDescriptor);

CoreRoutingDescriptor::CoreRoutingDescriptor() : cClassDescriptor("CoreRouting", "cObject")
{
}

CoreRoutingDescriptor::~CoreRoutingDescriptor()
{
}

bool CoreRoutingDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CoreRouting *>(obj)!=NULL;
}

const char *CoreRoutingDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CoreRoutingDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int CoreRoutingDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *CoreRoutingDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "outPort",
        "outLabel",
        "outColor",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int CoreRoutingDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outPort")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "outLabel")==0) return base+1;
    if (fieldName[0]=='o' && strcmp(fieldName, "outColor")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CoreRoutingDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *CoreRoutingDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CoreRoutingDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CoreRouting *pp = (CoreRouting *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CoreRoutingDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CoreRouting *pp = (CoreRouting *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getOutPort());
        case 1: return long2string(pp->getOutLabel());
        case 2: return long2string(pp->getOutColor());
        default: return "";
    }
}

bool CoreRoutingDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CoreRouting *pp = (CoreRouting *)object; (void)pp;
    switch (field) {
        case 0: pp->setOutPort(string2long(value)); return true;
        case 1: pp->setOutLabel(string2long(value)); return true;
        case 2: pp->setOutColor(string2long(value)); return true;
        default: return false;
    }
}

const char *CoreRoutingDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *CoreRoutingDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CoreRouting *pp = (CoreRouting *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


