package builder;

import NodePkg.Node;

public abstract class Builder implements IBuilder{
	abstract public void build(); 
	abstract public void setValue(Object val);
	abstract public void setNextReference(Node next);
	abstract public void setPrevReference(Node prev);
}