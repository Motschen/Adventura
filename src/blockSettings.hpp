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
        bool isBrittle() {
            return isBrittle_;
        }
        bool isClimbableFromTop() {
            return isClimbableFromTop_;
        }
        bool isClimbableFromBottom() {
            return isClimbableFromBottom_;
        }

        friend class BlockSettingsBuilder;

    private:
        bool isSolid_ = true;
        bool isPushable_ = false;
        bool isClimbableFromTop_ = false;
        bool isClimbableFromBottom_ = false;
        bool isLethal_ = false;
        bool isBrittle_ = false;
        bool hasCollision_ = false;
        bool hasGravity_ = false;
};
class BlockSettingsBuilder {
    public:
        BlockSettingsBuilder nonSolid() {
            blockSettings.isSolid_ = false;
            return *this;
        }
        BlockSettingsBuilder pushable() {
            blockSettings.isPushable_ = true;
            return *this;
        }
        BlockSettingsBuilder collidable() {
            blockSettings.hasCollision_ = true;
            return *this;
        }
        BlockSettingsBuilder gravity() {
            blockSettings.hasGravity_ = true;
            return *this;
        }
        BlockSettingsBuilder lethal() {
            blockSettings.isLethal_ = true;
            return *this;
        }
        BlockSettingsBuilder brittle() {
            blockSettings.isBrittle_ = true;
            return *this;
        }
        BlockSettingsBuilder climbableFromTop() {
            blockSettings.isClimbableFromTop_ = true;
            return *this;
        }
        BlockSettingsBuilder climbableFromBottom() {
            blockSettings.isClimbableFromBottom_ = true;
            return *this;
        }
        BlockSettings build() {
            return blockSettings;
        }
    private:
        BlockSettings blockSettings = BlockSettings();
};