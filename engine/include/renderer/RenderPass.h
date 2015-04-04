#ifndef RENDERPASS_H_
#define RENDERPASS_H_

namespace pdEngine
{

enum class RenderPass
{
    First,              
    Static = First,    
    Actor,            
    Sky,             
    NotRendered,    
    Last           
};

}

#endif /* RENDERPASS_H_ */
