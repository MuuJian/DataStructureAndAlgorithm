//
//  DebugDelete.h
//  DataStructureAndAlgorithm
//
//  Created by mumu on 6/3/2022.
//

#ifndef DebugDelete_h
#define DebugDelete_h

class DebugDelete {
public:
    DebugDelete(std::ostream& os = std::cerr) : os_(os) {}

    template<typename T>
    void operator()(T* p) const
    {
        os_ << "deleting unique_ptr" << std::endl;
        delete p;
    }

    
private:
    std::ostream& os_;
};

#endif /* DebugDelete_h */
