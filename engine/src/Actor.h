#ifndef ACTOR_H_
#define ACTOR_H_

#include <memory>

namespace pdEngine {

using ActorID = unsigned int;

constexpr ActorID NullActorID = 0;

class Actor
{
public:
    Actor ();
    virtual ~Actor ();

protected:

private:
};

using Actor_sptr = std::shared_ptr<Actor>;


}
#endif /* ACTOR_H_ */
