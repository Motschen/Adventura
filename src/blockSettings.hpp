class BlockSettings {
    public:
        BlockSettings() {}
        bool isSolid() {
            return isSolid_;
        }
        bool hasCollision() {
            return hasCollision_;
        }
        bool hasGravity() {
            return hasGravity_;
        }
        bool isPushable() {
            return isPushable_;
        }
        bool isLethal() {
            return isLethal_;
        }
        bool isClimbableFromTop() {
            return isClimbableFromTop_;
        }
        bool isClimbableFromBottom() {
            return isClimbableFromBottom_;
        }

        void setSolid(bool isSolid) {
            this->isSolid_ = isSolid;
        }
        void setPushable(bool isMovable) {
            this->isPushable_ = isMovable;
        }
        void setCollision(bool hasCollision) {
            this->hasCollision_ = hasCollision;
        }
        void setGravity(bool hasGravity) {
            this->hasGravity_ = hasGravity;
        }
        void setLethal(bool isLethal) {
            this->isLethal_ = isLethal;
        }
        void setClimbableFromTop(bool isClimbableFromTop) {
            this->isClimbableFromTop_ = isClimbableFromTop;
        }
        void setClimbableFromBottom(bool isClimbableFromBottom) {
            this->isClimbableFromBottom_ = isClimbableFromBottom;
        }

    private:
        bool isSolid_ = true;
        bool isPushable_ = false;
        bool isClimbableFromTop_ = false;
        bool isClimbableFromBottom_ = false;
        bool isLethal_ = false;
        bool hasCollision_ = false;
        bool hasGravity_ = false;
};
class BlockSettingsBuilder {
    public:
        BlockSettingsBuilder nonSolid() {
            blockSettings.setSolid(false);
            return *this;
        }
        BlockSettingsBuilder pushable() {
            blockSettings.setPushable(true);
            return *this;
        }
        BlockSettingsBuilder collidable() {
            blockSettings.setCollision(true);
            return *this;
        }
        BlockSettingsBuilder gravity() {
            blockSettings.setGravity(true);
            return *this;
        }
        BlockSettingsBuilder lethal() {
            blockSettings.setLethal(true);
            return *this;
        }
        BlockSettingsBuilder climbableFromTop() {
            blockSettings.setClimbableFromTop(true);
            return *this;
        }
        BlockSettingsBuilder climbableFromBottom() {
            blockSettings.setClimbableFromBottom(true);
            return *this;
        }
        BlockSettings build() {
            return blockSettings;
        }
    private:
        BlockSettings blockSettings = BlockSettings();
};