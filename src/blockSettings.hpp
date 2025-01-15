class BlockSettings {
    public:
        BlockSettings() {}
        bool isSolid() {
            return isSolid_;
        }
        bool isMovable() {
            return isMovable_;
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
        void setMovable(bool isMovable) {
            this->isMovable_ = isMovable;
        }
        void setClimbableFromTop(bool isClimbableFromTop) {
            this->isClimbableFromTop_ = isClimbableFromTop;
        }
        void setClimbableFromBottom(bool isClimbableFromBottom) {
            this->isClimbableFromBottom_ = isClimbableFromBottom;
        }

    private:
        bool isSolid_ = true;
        bool isMovable_ = false;
        bool isClimbableFromTop_ = false;
        bool isClimbableFromBottom_ = false;
};
class BlockSettingsBuilder {
    public:
        BlockSettingsBuilder nonSolid() {
            blockSettings.setSolid(false);
            return *this;
        }
        BlockSettingsBuilder movable() {
            blockSettings.setMovable(true);
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